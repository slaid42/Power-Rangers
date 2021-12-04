#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL_timer.h>
#include <SDL_image.h>
#include "SDL_ttf.h"
class Image// êëàññ êàðòèíêè
{
private:
	SDL_Surface* surf;
	int x, y;
	int w, h;
	char* directive;
	char* key;
public:
	Image() {
		surf = nullptr;
		x = 0;
		y = 0;
		directive = nullptr;
		key = nullptr;
	}
	Image(char* key, char* dir, int x_a, int y_a) : key(key), directive(dir),
		x(x_a), y(y_a)
	{

	}

	Image* operator=(const Image& other) {
		surf = other.surf;
		x = other.x;
		y = other.y;
		directive = other.directive;
		key = other.key;
	}
	Image* operator=(Image& other) {
		surf = other.surf;
		x = other.x;
		y = other.y;
		directive = other.directive;
		key = other.key;
		other.surf = nullptr;
	}
	void Load()
	{
		surf = IMG_Load(directive);
	}
	SDL_Surface* get_surf()
	{
		return surf;
	}
	int get_x()
	{
		return x;
	}
	int get_y()
	{
		return y;
	}
	void Disappear() {
		if (surf != nullptr)
		{
			delete surf;
		}
	}
	~Image()
	{
		if (surf != nullptr)
		{
			delete surf;
		}
	}


};
class Game_text : public Image
{
private:

	int x, y;
	int w, h;
	char* key;
	SDL_Surface* surf;

public:

	Game_text() {
		surf = nullptr;
		x = 0;
		y = 0;
		w = 0;
		h = 0;
		key = nullptr;
	}
	Game_text(char* key, int x_a, int y_a, int w, int h, SDL_Color col, char* text, SDL_Surface* surf) : key(key),
		x(x_a), y(y_a), w(w), h(h), surf(surf)
	{

	}

	Game_text* operator=(const Game_text& other) {
		surf = other.surf;
		x = other.x;
		y = other.y;
		w = other.w;
		h = other.h;
		key = other.key;
	}
	Game_text* operator=(Game_text& other) {
		surf = other.surf;
		x = other.x;
		y = other.y;
		w = other.w;
		h = other.h;
		key = other.key;
		other.surf = nullptr;
	}

	~Game_text()
	{
		if (surf != nullptr)
		{
			delete surf;
		}
	}


};


class Audio{
private:
	Mix_Music* music;
public:
	Audio(const char* directive) {
		music = Mix_LoadMUS(directive);
	}
	Audio() {
		music = nullptr;
	}
	Audio& operator= (const char* directive) {
		music = Mix_LoadMUS(directive);
	}
	void Play() {
		Mix_PlayMusic(music, -1);
	}
};
