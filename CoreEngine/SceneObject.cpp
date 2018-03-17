//
// Created by Juscelino Tanaka on 16/03/18.
//

#include "SceneObject.h"
#include "L.h"

SDL_Renderer * SceneObject::renderer = nullptr;

void SceneObject::SetImage(const char *imgPath, bool onlyAddToPool) {

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
    rect.x = position.x;
    rect.y = position.y;
    rect.w = imageSize.x * scale.x;
    rect.h = imageSize.y * scale.y;

    SDL_RenderCopy(renderer, currentTexture, nullptr, &rect);
}

void SceneObject::Destroy() {
    SDL_DestroyTexture(currentTexture);
}

void SceneObject::Update() { L::d(""); }

// this method returns the imageSize multiplied by the scale of the image
Vector2 SceneObject::getRealSize() {
    return Vector2(imageSize.x * scale.x, imageSize.y * scale.y);
}


