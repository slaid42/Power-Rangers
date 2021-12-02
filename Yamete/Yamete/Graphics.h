#pragma once
class Image// класс картинки
{
private:


	SDL_Surface* surf;
	int x, y;
	char* directive;
	char* key;


public:

	Image(char* key, char* dir, int x_a, int y_a) : key(key), directive(dir),
		x(x_a), y(y_a), surf()
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

};
class Audio
{

};