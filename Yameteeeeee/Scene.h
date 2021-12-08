#pragma once
#include <vector>
#include "Graphics.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL.h>
#include <SDL_timer.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "SDL_ttf.h"

char* CharSlipt(const char* content, int l, int r){
    /*
    int siz = 0;
    if(content = NULL){
        return nullptr;
    }
    else{
        const char* contentptr = &content[0];
        char* rptr;

        if(*rptr == NULL){
            while(*contentptr == NULL){
                contentptr++;
                siz++;
            }
            r = siz;
        }
*/
        char* res = new char[r-l];
        for(int i = 0; i < (r-l); i++){
            res[i] = content[l+i];
        }
    return res;
}


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
	void Add_image(char* id_name, char* direction, int& x_a, int& y_a, int& w, int& h);
	void Add_text(char* id_name, char* content, const char* font, int size, SDL_Color color, int& x, int& y, int& w, int& h, int screen_w);
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

void Scene::Add_text(const char* content, const char* font, int size, SDL_Color color, int& x, int& y, int& w, int& h, int screen_w){
    SDL_Surface *sDest;
    for(uint16_t i=0; i <= sizeof(content)*size/screen_w; i++ ){
        char* text = CharSlipt(content, i*screen_w, (1+i)*screen_w);
        TTF_Font *fnt = TTF_OpenFont(font, size);
        SDL_Surface *sText = TTF_RenderText_Blended(fnt, text, color);
        SDL_Rect dest;
        dest.w = w;
        dest.h = h;
        dest.x = x;
        dest.y = y;
        SDL_BlitSurface( sText, NULL, sDest, &dest );
        y+=size;
    }

    scene_texts.push_back(new Game_text(id_name, x, y, w, h, sDest));
}
void Scene::Add_image(char* id_name, char* direction, int& x_a, int& y_a, int& w, int& h)
{

	scene_images.push_back(new Image(id_name, direction, x_a, y_a, w, h));
}

void DrawTextWindow(SDL_Color color, int& x, int& y, int& w, int& h){
    SDL_Surface* surf = SDL_CreateRGBSurface(0,w,h,32,0,0,0,0);
}

