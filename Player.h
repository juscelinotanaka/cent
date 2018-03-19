//
// Created by Juscelino Tanaka on 16/03/18.
//

#ifndef CENT_PLAYEROBJECT_H
#define CENT_PLAYEROBJECT_H

#include "CoreEngine/CoreEngine.h"
#include "Bullet.h"

class Player: public SceneObject {
public:
    Player(const char *name);
    Bullet bullet;

    void Update() override;
    void OnCollisionDetected(SceneObject *other) override;
};


#endif //CENT_PLAYEROBJECT_H
