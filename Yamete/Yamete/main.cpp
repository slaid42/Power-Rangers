#include <iostream>
#include <functional>
#include <cassert>

#include <list>
#include <map>
#include <vector>



#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

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


void GameProcess(Game_Engine* engine);// вместо инита
// эту функцию должен определить разраб и в ней он будет объ€вл€ть эпизоды и сцены, а также их настраивать
// т.е по сути он будет кодить тут
//ATTENTION : ‘”Ќ ÷»я ћќ∆≈“ Ѕџ“№ Ќ≈ ќЅЏя¬Ћ≈Ќј

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

    Options* options = new Options();// настройки пользовател€


    options->Check_options();

    SDL_Window* window = SDL_CreateWindow("Yamete kudasaiiii", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);


    if (NULL == window)
    {
        std::cout << "Could not create window: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Renderer* sdl_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Renderer* renderer = new Renderer();// создаем рендерер

    NULL_EVENT.type = SDL_RegisterEvents(1);

    Game_Engine g_engine(window, sdl_renderer, renderer);// создаем движок

    GameProcess(&g_engine);// вызываем код пользовател€

    g_engine.Start();// начинаем обработку игрового процесса

    SDL_DestroyWindow(window);
    SDL_Quit();


    return EXIT_SUCCESS;
}

void GameProcess(Game_Engine* engine)
{
    Episode* ep0 = engine->New_episode("ep0");
    Scene* sc1 = ep0->Add_scene("sc1");
    SDL_Color clr = {255,100,100,0};
    int a = 50;
    int h = 0;
    int w = 0;
    int x = 100;
    int y = 100;
    int scr = 100;
    int siz = 15;
    int scrwidth = 50;
    SDL_Rect asd;
    asd.h =h;
    asd.w = w;
    asd.x = x;
    asd.y = y;
    sc1->Add_Background("Lol", "BtT7h9_WXSs.jpg", 800, 450);
    sc1->Add_image("Lol1","BtT7h9_WXSs.jpg", a, a, a, a );
    sc1->Add_text("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", "Pacifico.ttf", siz, clr, 50, 50, 50, 50, 15);
    Scene* sc2 = ep0->Add_scene("sc2");
    sc2->Add_Clicker();
    sc2->Add_Background("Lol", "Z_fcbb35b5.jpg", 800, 450);
    sc2->Add_text("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", "Pacifico.ttf", siz, clr, 50, 50, 50, 50, 15);
    Scene* sc3 = ep0->Add_scene("sc3");

    engine->values_holder.Add("sc3_has_been_seen", 0);

    ep0->AddPermAction(SDL_KEYDOWN, [](Game_Engine& eng, SDL_Event ev)->EngineInstruction {
        if (ev.key.keysym.sym == SDLK_UP)
        {
            std::cout << "Yamete kudasai!!!!~~~" << "\n";
            return EngineInstruction("nothing");
        }

        });

    Episode* ep1 = engine->New_episode("ep1");
    Scene* sc4 = ep1->Add_scene("sc4");
    sc1->Add_Choice(sc2, sc3);
    sc2->Add_Script(
        [sc1, sc4](ActionValues& val)->EngineInstruction
        {
            if (val.values_holder->Get("sc3_has_been_seen") == 0)
            {
                val.this_scene->Next_Scene(sc1);
                return EngineInstruction("continue");
            }
            else
            {
                val.this_scene->Next_Scene(sc4);
                return EngineInstruction("continue");
            }
        });
    sc3->Add_Script(
        [](ActionValues val)->EngineInstruction
        {
            val.values_holder->Change("sc3_has_been_seen", 1);
            return EngineInstruction("continue");
        }
    );

    sc3->Next_Scene(sc4);

}
