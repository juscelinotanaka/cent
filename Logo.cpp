//
// Created by Juscelino Tanaka on 30/03/18.
//

#include "Logo.h"

Logo::Logo(const char *name) : SceneObject(name)
{
    setImage("data/Ghostipede.bmp");
    centerPivot = Vector2((30*16 - imageSize.x) / 2, (30*16 - imageSize.y) / 2 - 16);
    position = CoreEngine::getScreenSize() / 2;
    center = imageSize / 2;
//    scale = Vector2::zero;
    tickUpdate = true;
}

void Logo::Update() {
    if (animating) {
        lerp += (float) (Time::deltaTime / duration);

        if (show) {
            position = Vector2::lerp(CoreEngine::getScreenSize() / 2, centerPivot, lerp);
            scale = Vector2::lerp(Vector2::zero, Vector2::one, lerp);
        } else {
            position = Vector2::lerp(centerPivot, CoreEngine::getScreenSize() / 2, lerp);
            scale = Vector2::lerp(Vector2::one, Vector2::zero, lerp);
        }

        if (lerp > 1) {
            animating = false;
            lerp = 0;

            if (show)
                show = false;
            else {
                enable = false;
                if (callback != nullptr)
                    callback();
            }
        }
    }
}

void Logo::FadeOut(std::function<void()> callback) {
    animating = true;
    this->callback = callback;
}
