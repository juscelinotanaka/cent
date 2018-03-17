//
// Created by Juscelino Tanaka on 16/03/18.
//

#ifndef CENT_SCENEOBJECT_H
#define CENT_SCENEOBJECT_H


#include "Vector2.h"
#include <SDL.h>
#include <iostream>
#include <vector>

class SceneObject {
public:
    // attributes
    const char *name;
    Vector2 position;
    float rotationZ;
    Vector2 scale = Vector2(1, 1);
    Vector2 velocity;
    Vector2 imageSize;

    // methods
    void SetImage(const char * imgPath, bool onlyAddToPool = false);
    void RenderOnScreen();
    void Destroy();
    Vector2 getRealSize();

    // virtual methods
    virtual void Update();

    // static methods
    static void SetGlobalRenderer(SDL_Renderer *pRenderer);
    bool tickUpdate = false;

private:
    SDL_Texture * currentTexture;
    std::vector<SDL_Texture *> texturePool;
    SDL_Rect rect;

    // static attributes
    static SDL_Renderer * renderer;
};


#endif //CENT_SCENEOBJECT_H
