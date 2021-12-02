
class Game_Engine//движок реализует эпизоды и сцены, обрабатыввает событи€
{
private:

	SDL_Event game_event;
	SDL_Window* window;
	SDL_Surface* wind_surf;
	SDL_Renderer* sdl_renderer;
	std::list<Episode*> episode_holder;//тут храним эпизоды
	Renderer* renderer;
	bool quit;

public:
	Game_Engine(SDL_Window* window_a, SDL_Renderer* render_a, Renderer* renderer_a);

	Scene* Hold_Scene(Scene* curr_scene);//реализаци€ сцены

	Episode* Hold_Episode(Episode* curr_episode);//реализаци€ эпизода

	Episode* New_episode(const char* name_a);//добавление эпизода

	void Start()//старт игры
	{

		if (episode_holder.size() != 0 && *episode_holder.begin() != nullptr)
		{
			Episode * curr_episode = Hold_Episode(*episode_holder.begin());
			while (curr_episode)
			{
				curr_episode = Hold_Episode(curr_episode);
			}
		}
	}

	void Action_Holder(Scene* scene);




};


Game_Engine::Game_Engine(SDL_Window* window_a, SDL_Renderer* render_a, Renderer* renderer_a) :
	window(window_a), sdl_renderer(render_a), renderer(renderer_a),
	game_event(), episode_holder(), wind_surf(SDL_GetWindowSurface(window)), quit(false) {}



Episode* Game_Engine::New_episode(const char* name_a)                                                                                                                          
{
	Episode* helper = new Episode(name_a);
	episode_holder.push_back(helper);
	return helper;
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
					Hold_Scene(*scene_iter);//пока што вызываем все сцены по очереди из списка сцен эпизода
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



Scene* Game_Engine::Hold_Scene(Scene* curr_scene)
{	
	if (!curr_scene) { return 0; }
	std::cout << curr_scene->get_name() << " is on action" << "\n";
	if (curr_scene->get_scene_images().size() != 0)
	{
		for (auto it = curr_scene->get_scene_images().begin(); it != curr_scene->get_scene_images().end(); ++it)
		{
			if ((*it) != nullptr)
			{
				(*it)->Load();//загружаем картинки, объ€вленные в сцене
			}
		}
	}

	bool on_work = true;
	while (on_work)// блок обработки событий
	{
		while (SDL_PollEvent(&game_event) != 0)
		{
			if (game_event.type == SDL_QUIT)
			{
				on_work = false;
				quit = true;
				break;
			}
			if (game_event.type == SDL_MOUSEBUTTONDOWN)
			{
				on_work = false;
			}
		}

		renderer->Update(wind_surf, sdl_renderer, curr_scene->get_scene_images());// рендер обновл€ет экран
	}


	return 0;
	
}