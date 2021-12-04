#pragma once
#include "Render.h"
#include "SDL.h"
#include <vector>
#include <string>
#include "Episode.h"
#include "Scene.h"



class Game_Engine//äâèæîê ðåàëèçóåò ýïèçîäû è ñöåíû, îáðàáàòûââàåò ñîáûòèÿ
{
private:

	SDL_Event game_event;
	SDL_Window* window;
	SDL_Surface* wind_surf;
	SDL_Renderer* sdl_renderer;
	Characters characters;
	ValuesHolder values_holder;
	std::list<Episode*> episode_holder;//òóò õðàíèì ýïèçîäû
	Renderer* renderer;
	bool quit;
	bool on_work;
	bool end_scene;

public:
	friend EngineInstruction;


	Game_Engine(SDL_Window* window_a, SDL_Renderer* render_a, Renderer* renderer_a);

	Scene* Hold_Scene(Episode* cur_episode, Scene* curr_scene);//ðåàëèçàöèÿ ñöåíû

	Episode* Hold_Episode(Episode* curr_episode);//ðåàëèçàöèÿ ýïèçîäà

	Episode* New_episode(const char* name_a);//äîáàâëåíèå ýïèçîäà



	void Start();


	void Action_Holder(Scene* scene);


	~Game_Engine();

};


Game_Engine::Game_Engine(SDL_Window* window_a, SDL_Renderer* render_a, Renderer* renderer_a) :
	window(window_a), sdl_renderer(render_a), renderer(renderer_a),
	game_event(), episode_holder(), wind_surf(SDL_GetWindowSurface(window)), quit(false), on_work(false), end_scene(false) {}



Episode* Game_Engine::New_episode(const char* name_a)
{
	Episode* helper = new Episode(name_a);
	episode_holder.push_back(helper);
	return helper;
}


void Game_Engine::Start()//ñòàðò èãðû
{

	if (episode_holder.size() != 0 && *episode_holder.begin() != nullptr)
	{
		Episode* curr_episode = *episode_holder.begin();//íà÷èíàåì ñ ïåðâîãî ýïèçîäà â ñïèñêå ýïèçîäîâ
		Scene* null_scene = curr_episode->Add_scene("null_scene");// äîáàâëÿåì íóëåâóþ ñöåíó, íà êîòîðóþ ïî äåôîëòó ññûëàþòñÿ âñå ñöåíû

		Scene* curr_scene = *curr_episode->get_scene_v()->begin();//íà÷èíàåì ñ ïåðâîé ñöåíû ïåðâîãî ýïèçîäà

		while (!quit)//ïîêà ïîëüçîâàòåëü íå âûéäåò èç èãðû áóäåì âûçûâàòü îáðàáîò÷èê ñöåíû
		{
			curr_scene = Hold_Scene(curr_episode, curr_scene);
		}
	}

}
Episode* Game_Engine::Hold_Episode(Episode* curr_episode)
{
	if (curr_episode)
	{	
		curr_episode->PlayAudio();
		std::cout << curr_episode->get_name() << " is on action" << "\n";
		if (curr_episode->get_scene_v()->size() != 0)
		{
			for (auto scene_iter = curr_episode->get_scene_v()->begin(); scene_iter != curr_episode->get_scene_v()->end(); ++scene_iter)
			{
				if (*scene_iter)
				{
					Hold_Scene(curr_episode, *scene_iter);//ïîêà øòî âûçûâàåì âñå ñöåíû ïî î÷åðåäè èç ñïèñêà ñöåí ýïèçîäà
				}
				if (quit)
				{
					break;
				}
			}
		}
		if (quit)
		{
			return nullptr;
		}
		if (curr_episode->get_next_episode())
		{
			return curr_episode->get_next_episode();
		}
		else
		{
			return nullptr;
		}
	}
}



Scene* Game_Engine::Hold_Scene(Episode* curr_episode, Scene* curr_scene)
{
	if (!curr_scene) { return 0; }// ïðîâåðÿåì øòî óêàçàòåëü íå ñëîìàí
	std::cout << curr_scene->get_name() << " is on action" << "\n";//âûâîäèì íàçâàíèå âîñïðîèçâîäèìîé ñöåíû
	curr_scene->Next_Scene(*(--curr_episode->get_scene_v()->end()));// äîáàâëÿåì äåôîëòíûé óêàçàòåëü íà ñëåäóþùóþ ñöåíó

	if (curr_scene->get_scene_images().size() != 0)
	{
		for (auto it = curr_scene->get_scene_images().begin(); it != curr_scene->get_scene_images().end(); ++it)
		{
			if ((*it) != nullptr)
			{
				(*it)->Load();//çàãðóæàåì êàðòèíêè, îáúÿâëåííûå â ñöåíå
			}
		}
	}

	on_work = true;// ïîêà ïåðåìåííàÿ òðó, áóäåò ïðîèñõîäèòü îáðàáîòêà action
	end_scene = false;// ïîêà ïåðåìåííàÿ ôîëñ, áóäåò ïðîèñõîäèòü îáðàáîòêà ñöåíû

	for (auto it = curr_scene->get_actions().begin(); it != curr_scene->get_actions().end(); it++)
	{	// ðåàëèçîâûâàåì âñå action äî òåõ ïîð ïîêà îíè íå êîí÷àòñÿ èëè íå ñðàáîòàåò next_scene
		if (!end_scene)
		{
			while (on_work)// áëîê îáðàáîòêè ñîáûòèé
			{
				while (SDL_PollEvent(&game_event) != 0)
				{
					if (game_event.type == SDL_QUIT)
					{
						on_work = false;
						end_scene = true;
						quit = true;
						break;
					}
					if (game_event.type == (*it).get_trigger())
					{
						EngineInstruction inst = (*it).do_action(characters, values_holder, curr_scene, game_event);
						if (inst.get_command() == "stop_scene")
						{
							end_scene = true;
						}

						on_work = false;
					}
				}

				renderer->Update(wind_surf, sdl_renderer, curr_scene->get_scene_images());// ðåíäåð îáíîâëÿåò ýêðàí
			}
		}
		else
		{
			break;
		}
	}
	std::cout << "next scene: " << curr_scene->get_next_scene()->get_name() << "\n";
	return curr_scene->get_next_scene();
}


Game_Engine::~Game_Engine()
{
	for (auto it = episode_holder.begin(); it != episode_holder.end(); ++it)
	{
		delete* it;
	}
}
