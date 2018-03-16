//
// Created by Juscelino Tanaka on 16/03/18.
//

#ifndef CENT_COREENGINE_H
#define CENT_COREENGINE_H

#include "SceneObject.h"
#include "Input.h"
#include "Time.h"
#include "L.h"
#include <vector>

class CoreEngine {
public:
    static void UpdateEvents();
    static void UpdateActions();
    static void UpdateRendering();

    static bool QuitApplication();
    static void SetGlobalRenderer(SDL_Renderer *pRenderer);
    static void AddSceneObject(SceneObject * object);

private:
    static std::vector<SceneObject*> sceneObjects;
    static SDL_Renderer *renderer;
};


#endif //CENT_COREENGINE_H
