#pragma once
#include <vector>
#include "Graphics.h"

class Scene
{
private:
	std::vector<Image*> scene_images;
	std::vector<Game_text*> scene_texts;
	std::vector < std::function<void(Characters&, ValuesHolder&)>>* actions;
	Audio music;
	const char* name;

public:
	Scene(const char* name_a);

	void Add_Background(char* id_name, char* direction, int screen_w, int screen_h);
	void Add_image(char* id_name, char* direction, int x_a, int y_a, int w, int h);
	void Create_text(char* id_name, char* content, const char* font, int size, SDL_Color color, SDL_Rect dest, int screen_w);
	void Add_text(char* id_name, char* direction, int x_a, int y_a, int w, int h);
	void Add_Choice(Scene* sc1, Scene* sc2);
	void Add_Action(std::function<void(Characters&, ValuesHolder&)> action);


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

void Scene::Add_Background(char* id_name, char* direction, int screen_w, int screen_h){
    scene_images.push_back(new Image(id_name, direction, 0, 0, screen_w, screen_h));
}

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
