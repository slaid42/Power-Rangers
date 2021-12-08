




class Game_Engine//движок реализует эпизоды и сцены, обрабатыввает события
{
private:

	SDL_Event game_event;
	SDL_Window* window;
    Renderer* renderer;
	std::list<Episode*> episode_holder;//тут храним эпизоды
	bool quit;
	bool on_work;
	bool end_scene;


	Scene* Hold_Scene(Episode* cur_episode, Scene* curr_scene);//реализация сцены

	void Hold_Episode(Episode* curr_episode);//реализация эпизода

	void Action_Holder(Episode* curr_episode, Scene* curr_scene);
public:
    SDL_Surface* wind_surf;
	SDL_Renderer* sdl_renderer;
	friend EngineInstruction;

	Characters characters;
	ValuesHolder values_holder;


	Game_Engine(SDL_Window* window_a, SDL_Renderer* render_a, Renderer* renderer_a);
	Episode* New_episode(const char* name_a);//добавление эпизода
	void Start();



	~Game_Engine();

};


Game_Engine::Game_Engine(SDL_Window* window_a, SDL_Renderer* render_a, Renderer* renderer_a) :
	window(window_a), sdl_renderer(render_a), renderer(renderer_a),
	game_event(), episode_holder(), wind_surf(SDL_GetWindowSurface(window)), quit(false), on_work(false),end_scene(false),
	values_holder(), characters() {}



Episode* Game_Engine::New_episode(const char* name_a)
{
	Episode* helper = new Episode(name_a);
	episode_holder.push_back(helper);
	return helper;
}


void Game_Engine::Start()//старт игры
{

	if (episode_holder.size() != 0 && *episode_holder.begin() != nullptr)//ATTENTION СПИСОК ЭПИЗОДОВ МОЖЕТ БЫТЬ ПУСТ
	{
		Episode* curr_episode = *episode_holder.begin();//начинаем с первого эпизода в списке эпизодов
		Hold_Episode(curr_episode);
		Scene* curr_scene = *curr_episode->get_scene_v()->begin();//начинаем с первой сцены первого эпизода
		//ATTENTON СПИСОК СЦЕН МОЖЕТ БЫТЬ ПУСТ
		while (!quit)//пока пользователь не выйдет из игры будем вызывать обработчик сцены
		{
			curr_scene = Hold_Scene(curr_episode, curr_scene);
			if (curr_scene->get_my_episode() != curr_episode)
			{
				curr_episode = curr_scene->get_my_episode();
				Hold_Episode(curr_episode);
			}
		}
	}
	else
	{
		std::cerr << "engine don't have episodes to run";
	}

}
void Game_Engine::Hold_Episode(Episode *curr_episode)
{
	if(curr_episode)
	{
		Scene* null_scene = curr_episode->Add_scene("null_scene");// добавляем нулевую сцену, на которую по дефолту ссылаются все сцены
		null_scene->Add_Clicker();
		std::cout << curr_episode->get_name() << " is in run" << "\n";
	}
	else
	{
		std::cerr << "bad episode pointer";
	}
}



Scene* Game_Engine::Hold_Scene(Episode* curr_episode, Scene* curr_scene)
{
	if (!curr_scene) { return 0; }//ATTENTION С УКАЗАТЕЛЕМ МОЖЕТ БЫТЬ ШТО-ТО НЕ ТО
	std::cout << curr_scene->get_name() << " is on action" << "\n";//ATTENTION МОЖЕТ БЫТЬ ТАК ШТО ИМЕНИ НЕТ
	curr_scene->Next_Scene(*(--curr_episode->get_scene_v()->end()));// добавляем дефолтный указатель на следующую сцену

	if (curr_scene->get_scene_images().size() != 0)//ATTENTION СПИСОК КАРТИНОК МОЖЕТ БЫТЬ ПУСТ
	{
		for (auto it = curr_scene->get_scene_images().begin(); it != curr_scene->get_scene_images().end(); ++it)
		{
			if ((*it) != nullptr)//ATTETION ИТЕРАТОР МОЖЕТ СЛУЧАЙНО УКАЗАТЬ НА ПУСТУЮ КАРТИНКУ
			{
				(*it)->Load();//загружаем картинки, объявленные в сцене
			}
		}
	}

	Action_Holder(curr_episode, curr_scene);


	if (!quit)
	{
		std::cout << "next scene: " << curr_scene->get_next_scene()->get_name() << "\n";//ATTETION С УКАЗАТЕЛЕМ НА СЛЕДУЮЩУЮ СЦЕНУ МОГУТ ВОЗНИКНУТЬ ПРОБЛЕМЫ
	}


	curr_scene->change_alp(curr_scene->actions.end());//ATTENTION ПРОВЕРКА УКАЗАТЕЛЯ
	return curr_scene->get_next_scene();//ATTENTION НУЖНО ПРОВЕРИТЬ УКАЗАТЕЛЬ НА СЛЕДУЮЩИЙ ЭПИЗОД


}


void Game_Engine::Action_Holder(Episode* curr_episode,  Scene* curr_scene)
{

	on_work = true;// пока переменная тру, будет происходить обработка action
	end_scene = false;// пока переменная фолс, будет происходить обработка сцены

	for (auto it = curr_scene->get_actions().begin(); it != curr_scene->get_actions().end(); ++it)
	{	// реализовываем все action до тех пор пока они не кончатся или не сработает next_scene

			curr_scene->change_alp(++it);//ATTENTION НУЖНО ПОСМОТРЕТЬ ШТО ИТЕРАТОР НЕ УКАЗЫВАЕТ НА КОНЕЦ СПИСКА
			--it;

		if (!end_scene)
		{
			on_work = true;
			while (on_work)// блок обработки событий
			{
				SDL_PushEvent(&NULL_EVENT);

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
						ActionValues act_val(&characters, &values_holder, curr_scene, game_event);
						EngineInstruction inst = (*it).do_action(act_val);
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

					for (auto it_2 = curr_episode->get_perm_actions().begin(); it_2 != curr_episode->get_perm_actions().end(); ++it_2)
					{

							if (game_event.type == it_2->get_trigger())
							{
								EngineInstruction inst2 = it_2->do_action(*this, game_event);

							}
					}


				}

				renderer->Update(wind_surf, window, curr_scene->get_scene_images(),curr_scene->get_scene_texts(), sdl_renderer);// рендер обновляет экран
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
