//
// Created by Juscelino Tanaka on 16/03/18.
//

#include "MushroomObject.h"
#include "GameManager.h"

MushroomObject::MushroomObject(char n[20]) {
    name = n;
}

void MushroomObject::OnCollisionDetected(SceneObject *other) {
    hits++;
    if (hits == 4) {
        GameManager::MushroomDestroyed(this);
    } else
        SetImageFromPool(hits);
}

