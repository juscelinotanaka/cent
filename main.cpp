#define SDL_MAIN_HANDLED
#include <SDL.h>
#include "CoreEngine/CoreEngine.h"
#include "PlayerObject.h"
#include "GameManager.h"


int main()
{
    SDL_bool hideMouse = SDL_TRUE;

    SDL_Init(SDL_INIT_VIDEO);
//    SDL_ShowCursor(SDL_DISABLE);
    SDL_SetRelativeMouseMode(hideMouse);

    CoreEngine::setScreenSize(Vector2(30 * 16, 30 * 16));
    auto window = SDL_CreateWindow("Ghostipede", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                   (int) CoreEngine::getScreenSize().x, (int) CoreEngine::getScreenSize().y, 0);
    auto renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    CoreEngine::setGlobalRenderer(renderer);

    GameManager::PrepareGame();

    GameManager::StartGame();

    while (!CoreEngine::QuitApplication())
    {
        CoreEngine::UpdateEvents();

        CoreEngine::UpdateActions();

        CoreEngine::UpdateCollisions();

        CoreEngine::UpdateRendering();

        if (Input::GetEscape()) {
            CoreEngine::ListAllObjects();
            hideMouse = hideMouse == SDL_TRUE ? SDL_FALSE : SDL_TRUE;
//            SDL_SetRelativeMouseMode(hideMouse);
        }
//        L::d("fps: %f (%f) - mouse pos: %s", Time::fps, Time::deltaTime, Input::mousePosition.toStr());
    }

    CoreEngine::DestroyAll();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}