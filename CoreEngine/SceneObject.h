//
// Created by Juscelino Tanaka on 16/03/18.
//

#ifndef CENT_SCENEOBJECT_H
#define CENT_SCENEOBJECT_H

#include <SDL.h>
#include <iostream>
#include <vector>
#include "Vector2.h"

class SceneObject {
public:
    // attributes
    explicit SceneObject(const char * name);
    const char *name;
    const char *tag;
    bool enable = true;
    bool tickUpdate = false;
    bool enableCollision = false;
    double rotationZ = 0;
    Vector2 position;
    Vector2 scale = Vector2::one;
    Vector2 center = Vector2::zero;

    // physics
    Vector2 velocity = Vector2::zero;
    Vector2 imageSize;
    Vector2 getRealSize();

    // methods, getters and setters
    void setImage(const char *imgPath, bool onlyAddToPool = false);
    void setImageFromPool(int i);
    Vector2 getGridPosition();
    std::vector<SDL_Texture *> * getSharedTexture();
    void setSharedTexture(std::vector<SDL_Texture *> *textures);
    bool isTag(const char * aTag);
    bool isName(const char * aName);
    void RenderOnScreen();
    void Destroy();

    // virtual methods
    virtual void Update();
    virtual void OnCollisionDetected(SceneObject *other);

    // static methods
    static void SetGlobalRenderer(SDL_Renderer *pRenderer);

protected:
    std::vector<SDL_Texture *> texturePool;


private:
    SDL_Texture * currentTexture;
    SDL_Rect rect;

    // static attributes
    static SDL_Renderer * renderer;

};


#endif //CENT_SCENEOBJECT_H
