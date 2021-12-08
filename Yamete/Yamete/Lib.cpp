#include <iostream>
#include <functional>

#include <list>
#include <map>
#include <vector>



#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "Options.h"
#include "Graphics.h"
#include "Values_holder.h"
#include "Characters.h"
#include "Action.h"
#include "scene.h"
#include "Episode.h"
#include "Renderer.h"
#include "Game_Engine.h"


const int WIDTH = 800, HEIGHT = 450;


void GameProcess(Game_Engine* engine);// ������ �����
// ��� ������� ������ ���������� ������ � � ��� �� ����� ��������� ������� � �����, � ����� �� �����������
// �.� �� ���� �� ����� ������ ���


int main(int argc, char* argv[])
{
    TTF_Init();
    atexit(TTF_Quit);
    SDL_Init(SDL_INIT_EVERYTHING);

    Options* options = new Options();// ��������� ������������


    options->Check_options();

    SDL_Window* window = SDL_CreateWindow("Yamete kudasaiiii", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);


    if (NULL == window)
    {
        std::cout << "Could not create window: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Renderer* sdl_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Renderer* renderer = new Renderer();// ������� ��������

    Game_Engine g_engine(window, sdl_renderer, renderer);// ������� ������

    GameProcess(&g_engine);// �������� ��� ������������

    g_engine.Start();// �������� ��������� �������� ��������

    SDL_DestroyWindow(window);
    SDL_Quit();


    return EXIT_SUCCESS;
}

void GameProcess(Game_Engine* engine)
{
    Episode* ep0 = engine->New_episode("ep0");
    Scene* sc1 = ep0->Add_scene("sc1");

}
