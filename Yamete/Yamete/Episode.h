class Engine;

class Episode
{
	
private:
	std::list<Scene*> scene_v;// вектор сцен, добавленных в эпизод
	const char* name;
	Episode* next_episode;// ссылка на следующий эпизод
public:
	
	Episode(const char* name_a);
	void Next_episode(Episode* next_episode);// добавить ссылку на следующий эпизод
	Scene* Add_scene(const char* name);//добавить новую сцену


	std::list<Scene*>* get_scene_v()
	{
		return &scene_v; 
	}

	const char* get_name()
	{
		return name;
	}

	Episode* get_next_episode()
	{
		return next_episode;
	}

	
};


Episode::Episode(const char* name_a) : scene_v(), name(name_a), next_episode(nullptr) {}

void Episode::Next_episode(Episode* next_episode_a)
{
	next_episode = next_episode_a;
}

Scene* Episode::Add_scene( const char* name)
{
	Scene* helper = new Scene(name);
	scene_v.push_back(helper);
	return helper;
}