#pragma once
class Image// класс картинки
{
private:
	SDL_Surface* surf;
	int x, y;
	int w, h;
	char* directive;
	char* key;
public:

	Image(char* key, char* dir, int x_a, int y_a, int w, int h) : key(key), directive(dir),
		x(x_a), y(y_a), w(w), h(h)
	{

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
	~Image()
	{
		if (surf != nullptr)
		{
			delete surf;
		}
	}


};
class Game_text
{
private:
	SDL_Surface* surf;
	int x, y;
	int w, h;
	char* directive;
	char* key;
	char* text;
};
class Audio
{

};
