




class Game_Engine//движок реализует эпизоды и сцены, обрабатыввает события
{
private:

	SDL_Event game_event;
	SDL_Window* window;
	SDL_Surface* wind_surf;
	SDL_Renderer* sdl_renderer;
	Characters characters;
	ValuesHolder values_holder;
	std::list<Episode*> episode_holder;//тут храним эпизоды
	Renderer* renderer;
	bool quit;
	bool on_work;
	bool end_scene;

public:
	friend EngineInstruction;


	Game_Engine(SDL_Window* window_a, SDL_Renderer* render_a, Renderer* renderer_a);

	Scene* Hold_Scene(Episode* cur_episode, Scene* curr_scene);//реализация сцены

	Episode* Hold_Episode(Episode* curr_episode);//реализация эпизода

	Episode* New_episode(const char* name_a);//добавление эпизода

	void Action_Holder(Scene* curr_scene);


	void Start();



	~Game_Engine();

};


Game_Engine::Game_Engine(SDL_Window* window_a, SDL_Renderer* render_a, Renderer* renderer_a) :
	window(window_a), sdl_renderer(render_a), renderer(renderer_a),
	game_event(), episode_holder(), wind_surf(SDL_GetWindowSurface(window)), quit(false), on_work(false),end_scene(false) {}



Episode* Game_Engine::New_episode(const char* name_a)                                                                                                                          
{
	Episode* helper = new Episode(name_a);
	episode_holder.push_back(helper);
	return helper;
}


void Game_Engine::Start()//старт игры
{

	if (episode_holder.size() != 0 && *episode_holder.begin() != nullptr)
	{
		Episode* curr_episode = *episode_holder.begin();//начинаем с первого эпизода в списке эпизодов
		Scene* null_scene = curr_episode->Add_scene("null_scene");// добавляем нулевую сцену, на которую по дефолту ссылаются все сцены

		Scene* curr_scene = *curr_episode->get_scene_v()->begin();//начинаем с первой сцены первого эпизода

		while (!quit)//пока пользователь не выйдет из игры будем вызывать обработчик сцены
		{
			curr_scene = Hold_Scene(curr_episode, curr_scene);
		}
	}
	else
	{
		std::cerr << "engine don't have episodes to run";
	}

}
Episode* Game_Engine::Hold_Episode(Episode *curr_episode)
{
	if (curr_episode)
	{	
		std::cout << curr_episode->get_name() << " is on action" << "\n";
		if (curr_episode->get_scene_v()->size() != 0)
		{
			for (auto scene_iter = curr_episode->get_scene_v()->begin(); scene_iter != curr_episode->get_scene_v()->end(); ++scene_iter)
			{
				if (*scene_iter)
				{
					Hold_Scene(curr_episode, *scene_iter);//пока што вызываем все сцены по очереди из списка сцен эпизода
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
	if (!curr_scene) { return 0; }// проверяем што указатель не сломан
	std::cout << curr_scene->get_name() << " is on action" << "\n";//выводим название воспроизводимой сцены
	curr_scene->Next_Scene(*(--curr_episode->get_scene_v()->end()));// добавляем дефолтный указатель на следующую сцену

	if (curr_scene->get_scene_images().size() != 0)
	{
		for (auto it = curr_scene->get_scene_images().begin(); it != curr_scene->get_scene_images().end(); ++it)
		{
			if ((*it) != nullptr)
			{
				(*it)->Load();//загружаем картинки, объявленные в сцене
			}
		}
	}

	Action_Holder(curr_scene);


	if (!quit)
	{
		std::cout << "next scene: " << curr_scene->get_next_scene()->get_name() << "\n";
	}


	curr_scene->change_alp(curr_scene->actions.end());
	return curr_scene->get_next_scene();


}


void Game_Engine::Action_Holder(Scene* curr_scene)
{

	on_work = true;// пока переменная тру, будет происходить обработка action
	end_scene = false;// пока переменная фолс, будет происходить обработка сцены

	for (auto it = curr_scene->get_actions().begin(); it != curr_scene->get_actions().end(); ++it)
	{	// реализовываем все action до тех пор пока они не кончатся или не сработает next_scene

			curr_scene->change_alp(++it);
			--it;

		if (!end_scene)
		{
			on_work = true;
			while (on_work)// блок обработки событий
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
							on_work = false;
						}
						if (inst.get_command() == "continue")
						{
							on_work = false;
						}

					}
				}

				renderer->Update(wind_surf, sdl_renderer, curr_scene->get_scene_images());// рендер обновляет экран
			}
		}
		else
		{	

			break;
		}
	}
}

Game_Engine::~Game_Engine()
{
	for (auto it = episode_holder.begin(); it != episode_holder.end(); ++it)
	{
		delete *it;
	}
}