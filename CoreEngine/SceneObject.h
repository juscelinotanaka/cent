//
// Created by Juscelino Tanaka on 16/03/18.
//

#ifndef CENT_SCENEOBJECT_H
#define CENT_SCENEOBJECT_H


#include "Vector2.h"
#include <SDL.h>
#include <iostream>

class SceneObject {
public:
    // attributes
    const char *name;
    Vector2 position;
    float rotationZ;
    Vector2 scale = Vector2(1, 1);
    Vector2 velocity;

    // methods
    void SetImage(const char * imgPath);
    void RenderOnScreen();
    void Destroy();

    // virtual methods
    virtual void Update();

    // static methods
    static void SetGlobalRenderer(SDL_Renderer *pRenderer);
    bool tickUpdate = false;

private:
    SDL_Texture * texture;
    SDL_Rect rect;
    Vector2 imageSize;
    int imageWidth;
    int imageHeight;

    // static attributes
    static SDL_Renderer * renderer;
};


#endif //CENT_SCENEOBJECT_H
