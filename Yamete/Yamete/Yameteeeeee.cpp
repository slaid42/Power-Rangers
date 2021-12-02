#include <iostream>
#include <functional>

#include <SDL.h>
//#include <SDL_image.h>

//typedef unsigned long SDL_Surface;
SDL_Surface* IMG_Load(char* arg) { return 0; }

#include <list>
#include <map>
#include <vector>

#include "Options.h"
#include "Graphics.h"
#include "Values_holder.h"
#include "Characters.h"
#include "scene.h"
#include "Episode.h"
#include "Renderer.h"
#include "Engine.h"




const int WIDTH = 800, HEIGHT = 450;


void GameProcess(Engine* engine);// вместо инита 
// эту функцию должен определить разраб и в ней он будет объявлять эпизоды и сцены, а также их настраивать
// т.е по сути он будет кодить тут





int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

    Options* options = new Options();// настройки пользователя

    
    options->Check_options();

    SDL_Window* window = SDL_CreateWindow("Yamete kudasaiiii", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);

  
    if (NULL == window)
    {
        std::cout << "Could not create window: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Renderer* sdl_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Renderer* renderer = new Renderer();// создаем рендерер

    Engine engine(window, sdl_renderer, renderer);// создаем движок

    GameProcess(&engine);// вызываем код пользователя

    engine.Start();// начинаем обработку игрового процесса
    
    SDL_DestroyWindow(window);
    SDL_Quit();


    return EXIT_SUCCESS;
}

void GameProcess(Engine* engine)// условный код пользователя
{
    
    Episode* ep0 = engine->New_episode("ep0");// добавили эпизод
    Scene* sc1 = ep0->Add_scene("sc1");// добавили сцену
    Scene* sc2 = ep0->Add_scene("sc2");
    
}