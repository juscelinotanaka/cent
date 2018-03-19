//
// Created by Juscelino Tanaka on 16/03/18.
//

#include "BulletObject.h"

BulletObject::BulletObject() {
    tickUpdate = true;
    enableCollision = true;

    name = "Player Bullet";
    tag = "Bullet";

    // 60 cells per second * 16 pixels per cell * scale = pixels-cells per second
    velocity = Vector2(0, -60 * 16);

    SetImage("data/Laser.bmp");
    scale = Vector2::one * 2;
}

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
        StopFire();
}

void BulletObject::OnCollisionDetected(SceneObject *other) {
    if (strcmp(other->tag, "Mushroom") == 0) {
        StopFire();
        other->OnCollisionDetected(this);
    }
}

void BulletObject::StopFire() {
    isFired = false;
    position = Vector2(-20, -20);
}
