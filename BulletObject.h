//
// Created by Juscelino Tanaka on 16/03/18.
//

#ifndef CENT_BULLETOBJECT_H
#define CENT_BULLETOBJECT_H


#include "CoreEngine/CoreEngine.h"

class BulletObject: public SceneObject {
public:
    BulletObject();
    void Update() override;
    bool isFired = false;
    void Fire(Vector2 position);
};


#endif //CENT_BULLETOBJECT_H
