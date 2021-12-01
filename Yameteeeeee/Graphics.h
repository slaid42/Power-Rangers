#pragma once
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
