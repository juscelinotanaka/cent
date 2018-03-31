#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <sstream>
#include "CoreEngine/CoreEngine.h"
#include "Player.h"
#include "GameManager.h"


int main()
{
    SDL_bool hideMouse = SDL_TRUE;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_SetRelativeMouseMode(hideMouse);

    CoreEngine::setScreenSize(Vector2(30 * 16, 30 * 16));
    auto window = SDL_CreateWindow("Ghostipede", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                   (int) CoreEngine::getScreenSize().x, (int) CoreEngine::getScreenSize().y, 0);

    CoreEngine::setWindow(window);
    auto renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    CoreEngine::setGlobalRenderer(renderer);

    GameManager::PrepareGame();

    bool playerQuited = false;
    while (!CoreEngine::QuitApplication() && !playerQuited)
    {
        CoreEngine::UpdateEvents();

        CoreEngine::UpdateActions();

        CoreEngine::UpdateCollisions();

        CoreEngine::UpdateRendering();

        if (!GameManager::isGameStarted() && Input::GetMouseUp()) {
            GameManager::StartGame();
        }

        if (Input::GetEscape()) {
            CoreEngine::ListAllObjects();
            hideMouse = hideMouse == SDL_TRUE ? SDL_FALSE : SDL_TRUE;
            std::stringstream scoreText;
            scoreText.str( "" );
            scoreText << "Your Statistics:" << std::endl
                      << "Ghosts Killed\t\t\t: " << GameManager::ghostKills << std::endl
                      << "Parts of Ghost Killed\t\t: " << GameManager::partsDestroyed << std::endl
                      << "Mushrooms Destroyed\t: " << GameManager::mushroomsDestroyed << std::endl
                      << "Deaths\t\t\t\t: " << GameManager::deaths << std::endl
                      << "TOTAL SCORE\t\t\t: " << GameManager::getTotalScore() << std::endl;

            L::MessageBox("Game Finished", scoreText.str().c_str());
            playerQuited = true;
        }
    }

    SDL_SetRelativeMouseMode(SDL_FALSE);
    CoreEngine::DestroyAll();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}