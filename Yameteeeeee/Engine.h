
#include "Render.h"
#include "SDL.h"
#include <vector>
#include <string>
#include "Episode.h"
#include "Scene.h"


class Engine//äâèæîê ðåàëèçóåò ýïèçîäû è ñöåíû, îáðàáàòûââàåò ñîáûòèÿ
{
private:

	SDL_Event game_event;
	SDL_Window* window;
	SDL_Surface* wind_surf;
	SDL_Renderer* sdl_renderer;
	std::vector<Episode*> episode_holder;//òóò õðàíèì ýïèçîäû
	Renderer* renderer;

public:
	Engine(SDL_Window* window_a, SDL_Renderer* render_a, Renderer* renderer_a);
	
	Engine(const Engine& eng) = delete;

	Engine(Engine& eng) = delete;

	Engine& operator=(const Engine& eng) = delete;

	Engine& operator= (Engine& eng) = delete;

	Scene* Hold_Scene(Scene* curr_scene);//ðåàëèçàöèÿ ñöåíû

	Episode* Hold_Episode(Episode* curr_episode);//ðåàëèçàöèÿ ýïèçîäà

	Episode* New_episode(const char* name_a);//äîáàâëåíèå ýïèçîäà

	void Start()//ñòàðò èãðû
	{
		Hold_Episode((*episode_holder.begin()));
	}

	void Action_Holder(Scene* scene);

	~Engine();



};


Engine::Engine(SDL_Window* window_a, SDL_Renderer* render_a, Renderer* renderer_a) :
	window(window_a), sdl_renderer(render_a), renderer(renderer_a),
	game_event(), episode_holder(), wind_surf(SDL_GetWindowSurface(window)) {}



Episode* Engine::New_episode(const char* name_a)
{
	episode_holder.push_back(new Episode(name_a));
	return (*episode_holder.end()) - 1;
}

Episode* Engine::Hold_Episode(Episode* curr_episode)
{
	for(auto scene_iter = curr_episode->scene_v.begin(); scene_iter != curr_episode->scene_v.end(); ++scene_iter)
	{ 
		Hold_Scene(*scene_iter);//ïîêà øòî âûçûâàåì âñå ñöåíû ïî î÷åðåäè èç ñïèñêà ñöåí ýïèçîäà
	}
	return curr_episode->next_episode;
}



Scene* Engine::Hold_Scene(Scene* curr_scene)
{	
	for (auto it = curr_scene->get_scene_images().begin(); it != curr_scene->get_scene_images().end(); ++it)
	{
		if ((*it) != nullptr)
		{
			(*it)->Load();//çàãðóæàåì êàðòèíêè, îáúÿâëåííûå â ñöåíå
		}
	}

	bool on_work = true;
	bool quit = false;
	while (on_work)// áëîê îáðàáîòêè ñîáûòèé
	{
		while (SDL_PollEvent(&game_event) != 0)
		{
			if (game_event.type == SDL_QUIT)
			{
				on_work = false;
				quit = true;
				break;
			}

		}
		renderer->Update(wind_surf, sdl_renderer, curr_scene->get_scene_images());// ðåíäåð îáíîâëÿåò ýêðàí
	}


	if (quit)
	{   //óòå÷êà ïàìÿòè
		SDL_DestroyRenderer(sdl_renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		exit;
	}

	return 0;
	
}
