//
// Created by Juscelino Tanaka on 30/03/18.
//

#ifndef CENT_LOGO_H
#define CENT_LOGO_H


#include "CoreEngine/CoreEngine.h"
#include <functional>

class Logo : public SceneObject {
public:
    void Update() override;

    bool animating = true;
    bool show = true;
    explicit Logo(const char *name);

    double duration = 1;
    float lerp = 0;

    std::function<void()> callback = nullptr;
    void FadeOut(std::function<void()> callback);

    Vector2 centerPivot;
};


#endif //CENT_LOGO_H
