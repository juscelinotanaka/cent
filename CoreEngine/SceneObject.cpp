//
// Created by Juscelino Tanaka on 16/03/18.
//

#include "SceneObject.h"
#include "L.h"

SDL_Renderer * SceneObject::renderer = nullptr;

void SceneObject::SetImage(const char *imgPath) {
    // temp surface
    if (renderer == nullptr)
        return;

    auto surface = SDL_LoadBMP(imgPath);
    imageWidth = surface->w;
    imageHeight = surface->h;
    SDL_SetColorKey(surface, SDL_TRUE, 0);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}

void SceneObject::SetGlobalRenderer(SDL_Renderer *pRenderer) {
    renderer = pRenderer;
}

void SceneObject::RenderOnScreen() {
    rect.x = position.x;
    rect.y = position.y;
    rect.w = imageWidth * scale.x;
    rect.h = imageHeight * scale.y;

    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

void SceneObject::Destroy() {
    SDL_DestroyTexture(texture);
}

void SceneObject::Update() { L::d(""); }
