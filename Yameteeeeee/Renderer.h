#pragma once
#include <SDL.h>
#include <vector>
#include "Graphics.h"

class Renderer// ðåíäåð îòðèñîâûâàåò âñå øòî íàõîäèòñÿ íà ýêðàíå
{
public:
	Renderer() = default;
	Renderer(const Renderer* rend) = delete;
	Renderer(Renderer* rend) = delete;
	Renderer& operator=(const Renderer* rend) = delete;
	Renderer& operator=(Renderer* rend) = delete;
	void Draw(SDL_Surface* img, int x, int y, SDL_Surface* screen) const
	{
		SDL_Rect dest;
		dest.x = x;
		dest.y = y;
		SDL_BlitSurface(img, NULL, screen, &dest);
	}
	void Update(SDL_Surface* wind_surf, SDL_Renderer* rend, std::vector<Image*> Surfaces_on_act)
	{
		SDL_RenderClear(rend);
		for (auto it = Surfaces_on_act.begin(); it != Surfaces_on_act.end(); ++it)
		{
			
			Draw((*it)->get_surf(), (*it)->get_x(), (*it)->get_y(), wind_surf);
		}
		SDL_RenderPresent(rend);
	}
};


















/*struct Image_atribute
{
	SDL_Surface* surf;
	int x, y;
	char* directive;
	char* key;
	

	Image_atribute(char* key, char* dir,  int x_a, int y_a): key(key), directive(dir),
	x(x_a), y(y_a) 
	{
		surf = IMG_Load(directive);

	}
};

class Renderer
{
private:

public:

	Renderer(SDL_Window* wind) : on_work(false), quit(false), GameEvent(), window(), Surfaces_on_act()
	{
		window = wind;
		SDL_Surface* wind_surf = SDL_GetWindowSurface(wind);
		rend = SDL_CreateRenderer(wind, -1, SDL_RENDERER_ACCELERATED);
		Surfaces_on_act = new std::map<char*, Image_atribute*>();
	}
	void Action_Text(std::string text)
	{

	}

	void To_Render()
	{
		on_work = true;
		while (on_work)
		{
			while (SDL_PollEvent(&GameEvent) != 0)
			{
				if (GameEvent.type == SDL_QUIT)
				{
					on_work = false;
					quit = true;
					break;
				}

			}
		}

		if (quit)
		{
			SDL_DestroyRenderer(rend);
			SDL_DestroyWindow(window);
			SDL_Quit();
			exit;
		}

	}


	void Image(char* key, char* direct, int x, int y)
	{
		Image_atribute* atri = new Image_atribute(key, direct, x, y);
		Surfaces_on_act->insert({ key, atri });
		Update();

	}

	void Delete_Image(std::string key)
	{

	}

	void Draw(SDL_Surface* img, int x, int y, SDL_Surface* screen) const
	{
		SDL_Rect dest;
		dest.x = x;
		dest.y = y;
		SDL_BlitSurface(img, NULL, screen, &dest);
	}
	void Update()
	{
		SDL_RenderClear(rend);
		for (auto it = Surfaces_on_act->begin(); it != Surfaces_on_act->end(); it++)
		{
			Image_atribute* atri = it->second;
			Draw(atri->surf, atri->x, atri->y, wind_surf);
		}
		SDL_RenderPresent(rend);
	}
};
*/
