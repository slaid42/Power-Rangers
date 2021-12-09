#pragma once


class Episode;
class Scene
{
private:

	std::vector<Image*> scene_images;
	std::vector<Game_text*> scene_texts;
	std::list<Action> actions;
	std::list<Action>::iterator action_list_pos;
	Episode* my_episode;
	Scene* next_scene;
	Audio music;
	const char* name;

	void change_alp(std::list<Action>::iterator arg)
	{
		action_list_pos = arg;
	}

	void change_my_episode(Episode* epi)
	{
		my_episode = epi;


	}

public:

	friend Game_Engine;
	friend Episode;

	Scene(const char* name_a);
	void Add_image(char* id_name, char* direction, int& x_a, int& y_a, int& w, int& h);
    void Add_Background(char* id_name, char* direction, int screen_w, int screen_h);
	void Add_text(const char* content, const char* font, int siz, SDL_Color color, int x, int y, int w, int h, int screen_w);

	std::list<Action>::iterator get_alp()
	{
		return action_list_pos;
	}

	void Add_Action(SDL_EventType event_type, std::function<EngineInstruction(ActionValues& act_val)> action_arg)
	{
		Action action(event_type, action_arg);
		push_action(action);
	}
	void Add_Script(std::function<EngineInstruction(ActionValues& act_val)> scr)
	{
		Action action(NULL_EVENT.type, scr);
		push_action(action);
	}

	void push_action(Action& action)
	{
		if (actions.size() < 1)
		{
			actions.push_back(action);
		}
		else
		{
			actions.emplace(action_list_pos, action);
		}
	}

	void Next_Scene(Scene* next_scene_arg)
	{

		Action action(NULL_EVENT.type,[next_scene_arg](ActionValues& act_val) -> EngineInstruction
			{
				act_val.this_scene->Next_Scene(next_scene_arg, "slyshen_krik_na_vsy_dolgopy");
				return EngineInstruction("stop_scene");

			});
		push_action(action);

	}


	void Add_Clicker()
	{
		Action action(SDL_MOUSEBUTTONDOWN, [](ActionValues& act_val)-> EngineInstruction
			{
				return EngineInstruction("continue");
				//усё, кликер ничего не делает
			});
		push_action(action);
	}

	void Add_Choice(Scene* sc1, Scene* sc2)
	{
		Action action(SDL_MOUSEBUTTONDOWN, [sc1, sc2](ActionValues& act_val)-> EngineInstruction
			{
				if (act_val.event.button.button == SDL_BUTTON_LEFT)
				{
					act_val.this_scene->Next_Scene(sc1);
					return EngineInstruction("continue");
				}
				if (act_val.event.button.button == SDL_BUTTON_RIGHT)
				{
					act_val.this_scene->Next_Scene(sc2);
					return EngineInstruction("continue");
				}
				return EngineInstruction("nothing");
			});
		push_action(action);
	}

	void Next_Scene(Scene* scene, const char* password)
	{
		if (password == "slyshen_krik_na_vsy_dolgopy")
		{
			next_scene = scene;
		}
	}

	const char* get_name()
	{
		return name;
	}
	std::list<Action>& get_actions()
	{
		return actions;
	}
	Scene* get_next_scene()
	{
		return next_scene;
	}
	std::vector<Image*>& get_scene_images()
	{
		return scene_images;
	}

    std::vector<Game_text*>& get_scene_texts()
	{
		return scene_texts;
	}

	Episode* get_my_episode()
	{
		return my_episode;
	}
};


Scene::Scene(const char* name_a): name(name_a), scene_images(), scene_texts(), next_scene(nullptr), actions (), action_list_pos()
{
	action_list_pos = actions.end();
}


void Scene::Add_Background(char* id_name, char* direction, int screen_w, int screen_h){
    scene_images.push_back(new Image(id_name, direction, 0, 0, screen_w, screen_h));
}

void Scene::Add_text(const char* content, const char* font, int siz, SDL_Color color, int x, int y, int w, int h, int screen_w){
    char* id_name = "Kekw";
    scene_texts.push_back(new Game_text(id_name, x, y, w, h, content, font, color, screen_w));
}

void Scene::Add_image(char* id_name, char* direction, int& x_a, int& y_a, int& w, int& h)
{
	scene_images.push_back(new Image(id_name, direction, x_a, y_a, w, h));
}
