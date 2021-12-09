#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL_timer.h>
#include <SDL_image.h>
#include "SDL_ttf.h"
#include <SDL_mixer.h>

void DrawImg(SDL_Surface *img, int x, int y, int w, int h, SDL_Surface *screen){
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    dest.w = w;
    dest.h = h;
    SDL_BlitScaled(img, NULL, screen, &dest);
}

void PrintText(SDL_Surface *sDest, const char* message, const char* font, int size, SDL_Color color, SDL_Rect dest){
    TTF_Font *fnt = TTF_OpenFont(font, size);
    SDL_Surface *sText = TTF_RenderText_Blended(fnt, message, color);
    SDL_BlitSurface( sText, NULL, sDest, &dest );
    SDL_FreeSurface( sText );
    TTF_CloseFont(fnt);
}

int min(int l, int r) {
    if (l < r) {
        return l;
    }
    else { return r; }
}

char* CharSlipt(const char* content, int l, int r) {
    std::string s(content);
    if(l >= s.size()){return " ";}
    std::string subs = s.substr(l, min( s.size() - l, r - l));
    int len = min((r - l - 1),(s.size() - l - 1));
    char* res = new char[len];
    strcpy(res, subs.c_str());
    return res;
}

void DrawSimpleButton(SDL_Surface* screen, int x, int y, int w, int h, const char* text, const char* font, int siz, int red, int green, int blue, int bred, int bgreen, int bblue){
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    dest.w = w;
    dest.h = h;
    SDL_FillRect(screen, &dest, SDL_MapRGB(screen->format, bred, bgreen, bblue));
    dest.x += siz/10;
    dest.y += siz/10;
    SDL_Color clr;
    clr.r = red;
    clr.g = green;
    clr.b = blue;
    PrintText(screen, text, font, siz, clr, dest);
}

void DrawImageButton(SDL_Surface* screen, SDL_Surface* img, int x, int y, int w, int h, const char* text, const char* font, int siz, int red, int green, int blue){
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    dest.w = w;
    dest.h = h;
    //(SDL_Surface *img, int x, int y, SDL_Surface *screen)
    DrawImg(img, x, y, w, h, screen);
    dest.x += siz/10;
    dest.y += siz/10;
    SDL_Color clr;
    clr.r = red;
    clr.g = green;
    clr.b = blue;
    PrintText(screen, text, font, siz, clr, dest);
}

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
	Image(char* key, char* dir, int x_a, int y_a, int w, int h) : key(key), directive(dir),
		x(x_a), y(y_a), w(w), h(h)
	{

	}

	Image& operator=(const Image& other) {
		surf = other.surf;
		x = other.x;
		y = other.y;
		directive = other.directive;
		key = other.key;
		return *this;
	}

    void DrawImg(SDL_Surface* scr){
        SDL_Rect dest;
        dest.x = x;
        dest.y = y;
        dest.w = w;
        dest.h = h;
        SDL_BlitScaled(surf, NULL, scr, &dest);
    }



	Image& operator=(Image& other) {
		surf = other.surf;
		x = other.x;
		y = other.y;
		directive = other.directive;
		key = other.key;
		other.surf = nullptr;
		return *this;
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
	int siz;
	char* key;
	const char* font;
	const char* content;
	SDL_Color clr;
	int scrw;
public:

	SDL_Surface* surf;

	Game_text() {
		surf = nullptr;
		x = 0;
		y = 0;
		w = 0;
		h = 0;
		key = nullptr;
	}
	Game_text(char* key, int x_a, int y_a, int w, int h, const char* content, const char* font, SDL_Color clr, int scrw) : key(key),
		x(x_a), y(y_a), w(w), h(h), content(content), font(font), clr(clr), scrw(scrw)
	{

	}

	Game_text& operator=(const Game_text& other) {
		surf = other.surf;
		x = other.x;
		y = other.y;
		w = other.w;
		h = other.h;
		key = other.key;
		return *this;
	}
	Game_text& operator=(Game_text& other) {
		surf = other.surf;
		x = other.x;
		y = other.y;
		w = other.w;
		h = other.h;
		key = other.key;
		return *this;
	}

void DrawText(SDL_Surface* surf){
    std::string s(content);
    for(uint16_t i=0; i <= s.size()*siz/scrw; i++){
        char* text = CharSlipt(content, i*scrw, (1+i)*scrw);
        TTF_Font *fnt = TTF_OpenFont(font, siz);
        SDL_Surface *sText = TTF_RenderText_Blended(fnt, text, clr);
        SDL_Rect dest;
        dest.w = w;
        dest.h = h;
        dest.x = x;
        dest.y = y;
        SDL_BlitSurface(sText, NULL, surf, &dest);
        y+=siz;
    }
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


