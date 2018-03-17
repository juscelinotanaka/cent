#define SDL_MAIN_HANDLED
#include <SDL.h>
#include "CoreEngine/CoreEngine.h"
#include "PlayerObject.h"


int main()
{
    SDL_bool hideMouse = SDL_TRUE;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_ShowCursor(SDL_DISABLE);
    SDL_SetRelativeMouseMode(hideMouse);

    CoreEngine::setScreenSize(Vector2(30 * 16, 30 * 16));

    auto window = SDL_CreateWindow("Ghostipede", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                   (int) CoreEngine::getScreenSize().x, (int) CoreEngine::getScreenSize().y, 0);
    auto renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    CoreEngine::setGlobalRenderer(renderer);

    PlayerObject * s = new PlayerObject("Main Char");
    s->scale = Vector2::one * 2;
//    s->position = (CoreEngine::getScreenSize() - s->getRealSize()) / 2;;

    CoreEngine::AddSceneObject(s);

    while (!CoreEngine::QuitApplication())
    {
        CoreEngine::UpdateEvents();

        CoreEngine::UpdateActions();

        if (Input::GetEscape()) {
            L::d("toggling");
            hideMouse = hideMouse == SDL_TRUE ? SDL_FALSE : SDL_TRUE;
            SDL_SetRelativeMouseMode(hideMouse);
        }

        CoreEngine::UpdateRendering();
//        L::d("fps: %f (%f) - mouse pos: %s", Time::fps, Time::deltaTime, Input::mousePosition.toStr());
    }

    s->Destroy();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}