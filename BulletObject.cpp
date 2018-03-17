//
// Created by Juscelino Tanaka on 16/03/18.
//

#include "BulletObject.h"

// fires a bullet at the position passed by the player
void BulletObject::Fire(Vector2 position) {
    if (isFired)
        return;

    this->isFired = true;
    this->position = position;
}

void BulletObject::Update() {
    if (!isFired)
        return;

    position = position + velocity * Time::deltaTime;

    if (position.y < -16) // off screen
        isFired = false;
}

BulletObject::BulletObject() {
    tickUpdate = true;

    // 60 cells per second * 16 pixels per cell = pixels-cells per second
    velocity = Vector2(0, -60 * 16);
    SetImage("data/Laser.bmp");
}
