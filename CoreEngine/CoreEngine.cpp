//
// Created by Juscelino Tanaka on 16/03/18.
//

#include "CoreEngine.h"
#include "../Mushroom.h"

SDL_Renderer * CoreEngine::renderer = nullptr;
std::vector<SceneObject*> CoreEngine::sceneObjects;
Vector2 CoreEngine::screenSize;
SDL_Window * CoreEngine::window;

/// calculates the the amount that one image A is overlapping image B
Vector2 CoreEngine::overlapAmount(SceneObject *objA, SceneObject *objB) {
    int leftA, rightA, topA, bottomA;
    int leftB, rightB, topB, bottomB;

    leftA = objA->position.x;
    rightA = objA->position.x + objA->getRealSize().x;
    topA = objA->position.y;
    bottomA = objA->position.y + objA->getRealSize().y;

    leftB = objB->position.x;
    rightB = objB->position.x + objB->getRealSize().x;
    topB = objB->position.y;
    bottomB = objB->position.y + objB->getRealSize().y;

    int top = topB - topA;
    int left = leftA - leftB;
    int right = rightA - rightB;

    Vector2 diff = objA->getRealSize() - objB->getRealSize();
    diff.x = abs(diff.x);
    diff.y = abs(diff.y);

    int x;
    int signal = Math::signal(left);

    if (abs(left) < diff.x)
        x = signal * objA->getRealSize().x;
    else
        x = signal * (objA->getRealSize().x - abs(signal == -1 ? left : right));

    signal = Math::signal(top);
    int y = -1 * signal * (objA->getRealSize().y - abs(top));

    return Vector2(x, y);
}

bool CoreEngine::overlaps(SceneObject *objA, SceneObject *objB) {

    int leftA, rightA, topA, bottomA, leftB, rightB, topB, bottomB;

    leftA = objA->position.x;
    rightA = objA->position.x + objA->getRealSize().x;
    topA = objA->position.y;
    bottomA = objA->position.y + objA->getRealSize().y;

    leftB = objB->position.x;
    rightB = objB->position.x + objB->getRealSize().x;
    topB = objB->position.y;
    bottomB = objB->position.y + objB->getRealSize().y;

    //If any of the sides from A are outside of B
    return !(bottomA <= topB || topA >= bottomB || rightA <= leftB || leftA >= rightB);

}

void CoreEngine::UpdateCollisions() {
    for (auto s : sceneObjects) {
        // check colision only for those which activated collision and are enable
        if (!s->enableCollision || !s->enable)
            continue;

        for (auto other : sceneObjects) {
            if (s == other || !other->enable)
                continue;

            if (overlaps(s, other)) {
                s->OnCollisionDetected(other);
            }
        }
    }
}

void CoreEngine::UpdateEvents() {
    // update values on other classes every tick of the SDL loop
    Time::UpdateTimer();
    Input::HandleEvents();
}

void CoreEngine::UpdateActions() {
    // loop applying all the actions for each object on scene
    for (auto s : sceneObjects) {
        if (!s->tickUpdate || !s->enable)
            continue;

        s->Update();
    }
}

void CoreEngine::UpdateRendering() {

    SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 0x00 );
    SDL_RenderClear(renderer);

    // draw mouse position for debugging
    bool drawMouseDebug = false;
    if (drawMouseDebug) {
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
        SDL_RenderDrawLine(renderer,
                           (int) Input::mousePosition.x - 10, (int) Input::mousePosition.y - 10,
                           (int) Input::mousePosition.x + 10, (int) Input::mousePosition.y + 10);

        SDL_RenderDrawLine(renderer,
                           (int) Input::mousePosition.x + 10, (int) Input::mousePosition.y - 10,
                           (int) Input::mousePosition.x - 10, (int) Input::mousePosition.y + 10);
    }


    // loop rendering each object on scene
    for (auto s : sceneObjects) {
        s->RenderOnScreen();
    }

    SDL_RenderPresent(renderer);
}

bool CoreEngine::QuitApplication() {
    return Input::Quit();
}

void CoreEngine::setGlobalRenderer(SDL_Renderer *pRenderer) {
    renderer = pRenderer;
    SceneObject::SetGlobalRenderer(pRenderer);
}

void CoreEngine::AddSceneObject(SceneObject *object) {
    auto s = object;

    sceneObjects.push_back(object);
}

void CoreEngine::setScreenSize(Vector2 scrSize) {
    screenSize = scrSize;

}

Vector2 CoreEngine::getScreenSize() {
    return screenSize;
}

void CoreEngine::DestroyAll() {
    for (int i = 0; i < sceneObjects.size(); ++i) {
        sceneObjects[i]->Destroy();
    }
}

void CoreEngine::ListAllObjects() {
    for (int i = 0; i < sceneObjects.size(); ++i) {
        if (sceneObjects[i] != nullptr)
            if (auto m = dynamic_cast<Mushroom *>(sceneObjects[i])) {
                L::d("%s[%d] - %s", sceneObjects[i]->name, m->id, sceneObjects[i]->getGridPosition().toStr());
                L::d("%s", sceneObjects[i]->position.toStr());
            } else
                L::d("%s - %s - %s", sceneObjects[i]->name, sceneObjects[i]->getGridPosition().toStr(), sceneObjects[i]->position.toStr());
        else
            L::d("Scene Object is null: %d", i);
    }
}

void CoreEngine::setWindow(SDL_Window *pWindow) {
    window = pWindow;
}




