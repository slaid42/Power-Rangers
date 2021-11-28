class Engine;

class Episode
{
private:
	std::vector<Scene*> scene_v;// вектор сцен, добавленных в эпизод
	const char* name;
	Episode* next_episode;// ссылка на следующий эпизод

public:
	


	Episode(const char* name_a);
	void Next_episode(Episode* next_episode);// добавить ссылку на следующий эпизод
	Scene* Add_scene(const char* name);//добавить новую сцену

	friend Engine;
};


Episode::Episode(const char* name_a) : scene_v(), name(name_a), next_episode(nullptr) {}

void Episode::Next_episode(Episode* next_episode_a)
{
	next_episode = next_episode_a;
}

Scene* Episode::Add_scene( const char* name)
{
	scene_v.push_back(new Scene(name));
	return (*scene_v.end()) - 1;
}