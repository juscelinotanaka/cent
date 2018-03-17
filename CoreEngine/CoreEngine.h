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
#include <vector>

class CoreEngine {
private:
    static std::vector<SceneObject*> sceneObjects;
    static SDL_Renderer *renderer;
    static Vector2 screenSize;

public:
    static void UpdateEvents();
    static void UpdateActions();
    static void UpdateRendering();

    static bool QuitApplication();
    static void AddSceneObject(SceneObject *object);

    static void setGlobalRenderer(SDL_Renderer *pRenderer);

    static void setScreenSize(Vector2 scrSize);
    static Vector2 getScreenSize();

};


#endif //CENT_COREENGINE_H
