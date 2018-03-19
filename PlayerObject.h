//
// Created by Juscelino Tanaka on 16/03/18.
//

#ifndef CENT_PLAYEROBJECT_H
#define CENT_PLAYEROBJECT_H

#include "CoreEngine/CoreEngine.h"
#include "BulletObject.h"

class PlayerObject: public SceneObject {
public:
    PlayerObject(const char *name);
    BulletObject bullet;

    void Update() override;
    void OnCollisionDetected(SceneObject *other) override;
};


#endif //CENT_PLAYEROBJECT_H
