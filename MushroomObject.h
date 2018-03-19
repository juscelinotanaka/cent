//
// Created by Juscelino Tanaka on 16/03/18.
//

#ifndef CENT_MUSHROOMOBJECT_H
#define CENT_MUSHROOMOBJECT_H

#include "CoreEngine/CoreEngine.h"

class MushroomObject: public SceneObject {
public:
    MushroomObject(char *n);

    void OnCollisionDetected(SceneObject *other) override;

    int hits = 0;
};


#endif //CENT_MUSHROOMOBJECT_H