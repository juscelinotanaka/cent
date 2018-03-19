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
    const char *tag;
    bool enable = true;
    Vector2 position;
    float rotationZ;
    Vector2 scale = Vector2(1, 1);

    // physics
    Vector2 velocity;
    Vector2 imageSize;
    Vector2 getRealSize();

    // methods
    void SetImage(const char * imgPath, bool onlyAddToPool = false);
    void RenderOnScreen();
    void Destroy();

    // virtual methods
    virtual void Update();
    virtual void OnCollisionDetected(SceneObject *other);

    // static methods
    static void SetGlobalRenderer(SDL_Renderer *pRenderer);
    bool tickUpdate = false;
    bool enableCollision = false;

    void setSharedTexture(std::vector<SDL_Texture *> *textures);
    std::vector<SDL_Texture *> * getSharedTexture();
    void SetImageFromPool(int i);

protected:
    std::vector<SDL_Texture *> texturePool;

private:
    SDL_Texture * currentTexture;
    SDL_Rect rect;

    // static attributes
    static SDL_Renderer * renderer;

};


#endif //CENT_SCENEOBJECT_H
