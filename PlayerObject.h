//
// Created by Juscelino Tanaka on 16/03/18.
//

#ifndef CENT_PLAYEROBJECT_H
#define CENT_PLAYEROBJECT_H


#include "CoreEngine/CoreEngine.h"

class PlayerObject: public SceneObject {
public:
    PlayerObject(const char *string);

    void Update();
};


#endif //CENT_PLAYEROBJECT_H
