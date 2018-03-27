//
// Created by Juscelino Tanaka on 16/03/18.
//

#ifndef CENT_COREENGINE_H
#define CENT_COREENGINE_H

#include "SceneObject.h"
#include "Input.h"
#include "Time.h"
#include "L.h"
#include "Math.h"
#include "Vector2.h"
#include "Vector2.h"
#include <vector>

class CoreEngine {
private:
    static std::vector<SceneObject*> sceneObjects;
    static SDL_Renderer *renderer;
    static Vector2 screenSize;

public:
    static void UpdateEvents();
    static void UpdateActions();
    static void UpdateCollisions();
    static void UpdateRendering();

    static bool QuitApplication();
    static void AddSceneObject(SceneObject *object);

    static void setGlobalRenderer(SDL_Renderer *pRenderer);

    static void setScreenSize(Vector2 scrSize);
    static Vector2 getScreenSize();

    static void DestroyAll();

    static void ListAllObjects();

    static bool overlaps(SceneObject *objA, SceneObject *objB);
    static Vector2 overlapAmount(SceneObject *objA, SceneObject *objB);

    static void setWindow(SDL_Window *pWindow);
    static SDL_Window *window;
};


#endif //CENT_COREENGINE_H
