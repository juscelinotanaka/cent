//
// Created by Juscelino Tanaka on 16/03/18.
//

#include "CoreEngine.h"
#include "../PlayerObject.h"

SDL_Renderer * CoreEngine::renderer = nullptr;
std::vector<SceneObject*> CoreEngine::sceneObjects;

void CoreEngine::UpdateEvents() {
    Time::UpdateTimer();
    Input::HandleEvents();
}

void CoreEngine::UpdateActions() {

//    L::d("updating scene objects: %d", sceneObjects.size());

    // loop applying all the actions for each object on scene
    for (int i = 0; i < sceneObjects.size(); ++i) {
        auto * s = sceneObjects[i];

        if (!s->tickUpdate)
            continue;

        s->Update();
    }
}

void CoreEngine::UpdateRendering() {
    SDL_RenderClear(renderer);

    // loop rendering each object on scene
    for (int i = 0; i < sceneObjects.size(); ++i) {
        sceneObjects[i]->RenderOnScreen();
    }

    SDL_RenderPresent(renderer);
}

bool CoreEngine::QuitApplication() {
    return Input::Quit();
}

void CoreEngine::SetGlobalRenderer(SDL_Renderer *pRenderer) {
    renderer = pRenderer;
    SceneObject::SetGlobalRenderer(pRenderer);
}

void CoreEngine::AddSceneObject(SceneObject * object) {
    auto s = object;


    std::string ss = typeid(s).name();
    bool isit = typeid(s) == typeid(PlayerObject);
    L::d("adding: %s ~%s~ %d", s->name, ss.c_str(), isit);

    sceneObjects.push_back(object);
}
