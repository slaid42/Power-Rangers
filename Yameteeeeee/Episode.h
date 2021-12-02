#include <list>
#include "Episode.h"

class Engine;

class Episode
{
	
private:
	std::list<Scene*> scene_v;// âåêòîð ñöåí, äîáàâëåííûõ â ýïèçîä
	const char* name;
	Episode* next_episode;// ññûëêà íà ñëåäóþùèé ýïèçîä
public:
	
	Episode(const char* name_a);
	void Next_episode(Episode* next_episode);// äîáàâèòü ññûëêó íà ñëåäóþùèé ýïèçîä
	Scene* Add_scene(const char* name);//äîáàâèòü íîâóþ ñöåíó


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
