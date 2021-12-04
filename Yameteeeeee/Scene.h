#pragma once
class Scene 
{
private:

	std::vector<Image*> scene_images;
	std::vector<Game_text> scene_texts;
	std::vector<Action> actions;
	Scene* next_scene;
	const char* name;

public:
	Scene(const char* name_a);

	void Add_image(char* id_name, char* direction, int x_a, int y_a);
	void Add_text(char* id_name, char* content);
	void Add_Choice(Scene* sc1, Scene* sc2);
	void Add_Action(std::function<void(Characters&, ValuesHolder&)> action);

	void Next_Scene(Scene* next_scene_arg)
	{
		
		Action action(SDL_MOUSEBUTTONDOWN, [next_scene_arg](Characters& ch, ValuesHolder& vh, Scene* scene, SDL_Event eventt) -> EngineInstruction
			{
				scene->Next_Scene(next_scene_arg, "slyshen_krik_na_vsy_dolgopy");
				return EngineInstruction("stop_scene");
			});
		actions.push_back(action);
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
	std::vector<Action>& get_actions()
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


Scene::Scene(const char* name_a): name(name_a), scene_images(), scene_texts(), next_scene(nullptr) {}


void Scene::Create_text(char* id_name, char* content, const char* font, int size, SDL_Color color, SDL_Rect dest, screen_w){
    SDL_Surface *sDest;
    for(uint16_t i=0; i++; i <= sizeof(content)*size/screen_w){
        char* text = content.substr(i*screen_w, (1+i)screen_w);
        TTF_Font *fnt = TTF_OpenFont(font, size);
        SDL_Surface *sText = TTF_RenderText_Blended(fnt, text, color);
        SDL_BlitSurface( sText, NULL, dest, &dest );
        dest.y+=size;
    }
    text1 = new Game_text(id_name, NULL, SDL_Rect.x, SDL_Rect.y, SDL_Rect.w, SDL_Rect.h));
    text1.surf = sDest;
    scene_images.push_back(text1);
    TTF_CloseFont(fnt);
}

void Scene::Add_text(char* id_name, char* direction, int x_a, int y_a, int w, int h)
{

	scene_texts.push_back(new Game_text(id_name, direction, x_a, y_a, w, h));
}

void Scene::Add_image(char* id_name, char* direction, int x_a, int y_a, int w, int h)
{

	scene_images.push_back(new Image(id_name, direction, x_a, y_a, w, h));
}
