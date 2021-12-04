#pragma once
class Scene 
{
private:

	std::vector<Image*> scene_images;
	std::vector<Game_text> scene_texts;
	std::list<Action> actions;
	std::list<Action>::iterator action_list_pos;
	Scene* next_scene;
	Audio music;
	const char* name;

	void change_alp(std::list<Action>::iterator arg)
	{
		action_list_pos = arg;
	}

public:

	friend Game_Engine;

	Scene(const char* name_a);

	void Add_image(char* id_name, char* direction, int x_a, int y_a);
	void Add_text(char* id_name, char* content);
	void Add_Action(std::function<void(Characters&, ValuesHolder&)> action);

	std::list<Action>::iterator get_alp()
	{
		return action_list_pos;
	}


	void Add_Action(std::function<EngineInstruction(Characters&, ValuesHolder&, Scene*, SDL_Event)>)
	{

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
		
		Action action(SDL_MOUSEBUTTONDOWN,[next_scene_arg](Characters& ch, ValuesHolder& vh, Scene* scene, SDL_Event eventt) -> EngineInstruction
			{
				scene->Next_Scene(next_scene_arg, "slyshen_krik_na_vsy_dolgopy");
				return EngineInstruction("stop_scene");
			});
		push_action(action);

	} 

	
	void Add_Clicker()
	{
		Action action(SDL_MOUSEBUTTONDOWN, [](Characters& ch, ValuesHolder& vh, Scene* scene, SDL_Event event)-> EngineInstruction
			{
				return EngineInstruction("continue");
				//усё, кликер ничего не делает
			});
		push_action(action);
	}

	void Add_Choice(Scene* sc1, Scene* sc2)
	{
		Action action(SDL_MOUSEBUTTONDOWN, [sc1, sc2](Characters& ch, ValuesHolder& vh, Scene* scene, SDL_Event event)-> EngineInstruction
			{
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					scene->Next_Scene(sc1);
					return EngineInstruction("continue");
				}
				if (event.button.button == SDL_BUTTON_RIGHT)
				{
					scene->Next_Scene(sc2);
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
	

};


Scene::Scene(const char* name_a): name(name_a), scene_images(), scene_texts(), next_scene(nullptr), actions (), action_list_pos()
{
	action_list_pos = actions.end();
}

void Scene::Add_image(char* id_name, char* direction, int x_a, int y_a)
{
	
	scene_images.push_back(new Image(id_name, direction, x_a, y_a));
}
