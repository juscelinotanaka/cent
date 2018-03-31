//
// Created by Juscelino Tanaka on 30/03/18.
//

#ifndef CENT_LOGO_H
#define CENT_LOGO_H


#include "CoreEngine/CoreEngine.h"

class Logo : public SceneObject {
public:
    bool animating = true;
    bool show = true;
    explicit Logo(const char *name);
    void Update() override;

    double duration = 1;
    float lerp = 0;

    std::function<void()> callback = nullptr;
    void FadeOut(std::function<void()> callback);
};


#endif //CENT_LOGO_H
