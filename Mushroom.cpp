//
// Created by Juscelino Tanaka on 16/03/18.
//

#include "Mushroom.h"
#include "GameManager.h"

Mushroom::Mushroom(const char *name)  : SceneObject(name) {
}

void Mushroom::OnCollisionDetected(SceneObject *other) {
    hits++;
    if (hits == 4) {
        GameManager::MushroomDestroyed(this);
    } else
        setImageFromPool(hits);
}

