//
// Created by Juscelino Tanaka on 16/03/18.
//

#include "CoreEngine.h"

SDL_Renderer * CoreEngine::renderer = nullptr;
std::vector<SceneObject*> CoreEngine::sceneObjects;
Vector2 CoreEngine::screenSize;

Vector2 CoreEngine::overlapAmount(SceneObject *objA, SceneObject *objB) {
    SceneObject a = *objA;
    SceneObject b = *objB;

    int leftA, rightA, topA, bottomA;
    int leftB, rightB, topB, bottomB;

    leftA = a.position.x;
    rightA = a.position.x + a.getRealSize().x;
    topA = a.position.y;
    bottomA = a.position.y + a.getRealSize().y;

    leftB = b.position.x;
    rightB = b.position.x + b.getRealSize().x;
    topB = b.position.y;
    bottomB = b.position.y + b.getRealSize().y;

    int top = topB - topA;
    int bottom = bottomB - bottomA;
    int left = leftA - leftB;
    int right = rightA - rightB;

    Vector2 diff = a.getRealSize() - b.getRealSize();
    diff.x = abs(diff.x);
    diff.y = abs(diff.y);

    int x;
    int signal = Math::Signal(left);

    if (abs(left) < diff.x)
        x = signal * a.getRealSize().x;
    else
        x = signal * (a.getRealSize().x - abs(signal == -1 ? left : right));

    signal = Math::Signal(top);
    int y = -1 * signal * (a.getRealSize().y - abs(top));

    L::d("%d %d %d", top, abs(top), y);

    return Vector2(x, y);
}

bool CoreEngine::overlaps(SceneObject *objA, SceneObject *objB) {

    SceneObject a = *objA;
    SceneObject b = *objB;

    int leftA, rightA, topA, bottomA;
    int leftB, rightB, topB, bottomB;

    leftA = a.position.x;
    rightA = a.position.x + a.getRealSize().x;
    topA = a.position.y;
    bottomA = a.position.y + a.getRealSize().y;

    leftB = b.position.x;
    rightB = b.position.x + b.getRealSize().x;
    topB = b.position.y;
    bottomB = b.position.y + b.getRealSize().y;

    //If any of the sides from A are outside of B
    return (bottomA <= topB || topA >= bottomB || rightA <= leftB || leftA >= rightB) ? false : true;

}

void CoreEngine::UpdateCollisions() {
    for (auto s : sceneObjects) {
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
    SDL_RenderClear(renderer);

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
            L::d(sceneObjects[i]->name);
        else
            L::d("Scene Object is null: %d", i);
    }
}




