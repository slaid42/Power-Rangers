#pragma once
class Scene 
{
private:

	


	std::vector<Image*> scene_images;
	std::vector<Game_text*> scene_texts;
	std::vector<Action*> Actions;
	Audio music;
	const char* name;

public:
	Scene(const char* name_a);

	void Add_image(char* id_name, char* direction, int x_a, int y_a);
	void Add_text(char* id_name, char* content);
	void Add_Choice(Scene* sc1, Scene* sc2);
	void Add_Action(std::function<void(Characters&, ValuesHolder&)> action);

	const char* get_name()
	{
		return name;
	}

	std::vector<Image*> get_scene_images()
	{
		return scene_images;
	}


	~Scene()
	{
		delete actions;
	}

	
	
};


Scene::Scene(const char* name_a): name(name_a), scene_images(), scene_texts(){}

void Scene::Add_image(char* id_name, char* direction, int x_a, int y_a)
{
	
	scene_images.push_back(new Image(id_name, direction, x_a, y_a));
}
