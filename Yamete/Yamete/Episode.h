class Engine;

class Episode
{
	
private:
	std::list<Scene*> scene_v;// вектор сцен, добавленных в эпизод
	const char* name;
	Episode* next_episode;// ссылка на следующий эпизод
	std::list<PermAction> permanent_actions;
	
	std::list<PermAction>& get_perm_actions()
	{
		return permanent_actions;
	}
public:
	
	friend Game_Engine;

	Episode(const char* name_a);
	void Next_episode(Episode* next_episode);// добавить ссылку на следующий эпизод
	Scene* Add_scene(const char* name);//добавить новую сцену


	std::list<Scene*>* get_scene_v()
	{
		return &scene_v; 
	}

	void AddPermAction(Uint32 type, std::function<EngineInstruction(Game_Engine&, SDL_Event )> act)
	{
		PermAction action(type, act);
		permanent_actions.push_back(action);
	}

	const char* get_name()
	{
		return name;
	}

	Episode* get_next_episode()
	{
		return next_episode;
	}

	~Episode();
};


Episode::Episode(const char* name_a) : scene_v(), name(name_a), next_episode(nullptr) {}

void Episode::Next_episode(Episode* next_episode_a)
{
	next_episode = next_episode_a;
}

Scene* Episode::Add_scene( const char* name)
{
	Scene* helper = new Scene(name);
	helper->change_my_episode(this);
	scene_v.push_back(helper);
	return helper;
}

Episode::~Episode()
{
	for (auto it = scene_v.begin(); it != scene_v.end(); ++it)
	{
		delete *it;
	}
}