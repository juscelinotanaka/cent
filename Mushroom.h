//
// Created by Juscelino Tanaka on 16/03/18.
//

#ifndef CENT_MUSHROOMOBJECT_H
#define CENT_MUSHROOMOBJECT_H

#include "CoreEngine/CoreEngine.h"

class Mushroom: public SceneObject {
public:
    explicit Mushroom(const char *name);

    int id = 0;

    void OnCollisionDetected(SceneObject *other) override;
    void resetMushroom();

    int hits = 0;
};


#endif //CENT_MUSHROOMOBJECT_H
