//
// Created by Juscelino Tanaka on 16/03/18.
//

#include "SceneObject.h"
#include "L.h"
#include "CoreEngine.h"

SDL_Renderer * SceneObject::renderer = nullptr;

void SceneObject::setImage(const char *imgPath, bool onlyAddToPool) {

    if (renderer == nullptr)
        return;

    SDL_Surface * surface = SDL_LoadBMP(imgPath);
    imageSize.x = surface->w;
    imageSize.y = surface->h;
    SDL_SetColorKey(surface, SDL_TRUE, 0);

    auto tempTexture = SDL_CreateTextureFromSurface(renderer, surface);

    if (!onlyAddToPool)
        currentTexture = tempTexture;

    texturePool.push_back(tempTexture);
    SDL_FreeSurface(surface);
}

void SceneObject::SetGlobalRenderer(SDL_Renderer *pRenderer) {
    renderer = pRenderer;
}

void SceneObject::RenderOnScreen() {
    if (currentTexture == nullptr || !enable)
        return;

    // (int) = pixel perfect
    rect.x = (int)position.x;
    rect.y = (int)position.y;
    rect.w = (int)(imageSize.x * scale.x);
    rect.h = (int)(imageSize.y * scale.y);

    SDL_RenderCopy(renderer, currentTexture, nullptr, &rect);
}

void SceneObject::Destroy() {
    SDL_DestroyTexture(currentTexture);
}

// this method returns the imageSize multiplied by the scale of the image
Vector2 SceneObject::getRealSize() {
    return Vector2(imageSize.x * scale.x, imageSize.y * scale.y);
}

void SceneObject::setSharedTexture(std::vector<SDL_Texture *> *textures) {
    this->texturePool = *textures;
}

std::vector<SDL_Texture *> * SceneObject::getSharedTexture() {
    return &texturePool;
}

void SceneObject::setImageFromPool(int i) {
    currentTexture = texturePool[i];
}

void SceneObject::Update() { L::d("Generic Update. It should be override."); }
void SceneObject::OnCollisionDetected(SceneObject *other) {
    L::d("Generic Collision. It should be override. - other: %s", other != nullptr ? other->tag : "null");
}

SceneObject::SceneObject(const char * name) {
    this->name = name;
}

bool SceneObject::isTag(const char *aTag) {
    return !strcmp(tag, aTag);
}

bool SceneObject::isName(const char *aName) {
    return !strcmp(name, aName);
}

Vector2 SceneObject::getGridPosition() {
//    L::d("%f / %f : %d", position.x, CoreEngine::getScreenSize().x, (int) ceil(position.x / CoreEngine::getScreenSize().x));
    return {std::max((int) floor(30 * (position.x+0.001) / CoreEngine::getScreenSize().x), -1),
            std::min((int) floor(30 * (position.y+0.001) / CoreEngine::getScreenSize().y), 29)};
}

