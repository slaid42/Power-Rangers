#pragma once

void DrawImg(SDL_Surface *img, int x, int y, int w, int h, SDL_Surface *screen){
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    dest.w = w;
    dest.h = h;
    SDL_BlitScaled(img, NULL, screen, &dest);
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
    std::cout << res << std::endl;
    return res;
}

void PrintText(SDL_Surface *sDest, const char* message, const char* font, int size, SDL_Color color, SDL_Rect dest){
    TTF_Font *fnt = TTF_OpenFont(font, size);
    SDL_Surface *sText = TTF_RenderText_Blended(fnt, message, color);
    SDL_BlitSurface( sText, NULL, sDest, &dest );
    SDL_FreeSurface( sText );
    TTF_CloseFont(fnt);
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
