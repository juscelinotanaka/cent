#define SDL_MAIN_HANDLED
#include <SDL.h>
#include "CoreEngine/CoreEngine.h"
#include "PlayerObject.h"


int main()
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_ShowCursor(SDL_DISABLE);
    auto window = SDL_CreateWindow("Ghostipede", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 30 * 16, 30 * 16, 0);
    auto renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    CoreEngine::SetGlobalRenderer(renderer);

    PlayerObject *s = new PlayerObject("Main Char");

    s->position = Vector2::zero;
    s->scale = Vector2::one * 2;
    s->SetImage("data/Player.bmp");

    CoreEngine::AddSceneObject(s);

    while (!CoreEngine::QuitApplication())
    {
        CoreEngine::UpdateEvents();

        CoreEngine::UpdateActions();

        CoreEngine::UpdateRendering();
//        L::d("fps: %f (%f) - mouse pos: %s", Time::fps, Time::deltaTime, Input::mousePosition.toStr());
    }

    s->Destroy();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}