//
// Created by Juscelino Tanaka on 16/03/18.
//

#include "Bullet.h"

Bullet::Bullet() : SceneObject("Player Bullet") {
    tickUpdate = true;
    enableCollision = true;

    name = "Player Bullet";
    tag = "Bullet";

    // 60 cells per second * 16 pixels per cell * scale = pixels-cells per second
    velocity = Vector2(0, -60 * 16);

    setImage("data/Laser.bmp");
    scale = Vector2::one * 2;

    StopFire();
}

void Bullet::Update() {
    if (!isFired)
        return;

    position = position + velocity * Time::deltaTime;

    if (position.y < -16) // off screen
        StopFire();
}

// fires a bullet at the position passed by the player
void Bullet::Fire(Vector2 position) {
    if (isFired)
        return;

    this->isFired = true;
    this->position = position;
}

void Bullet::OnCollisionDetected(SceneObject *other) {
    if (strcmp(other->tag, "Mushroom") == 0) {
        StopFire();
        other->OnCollisionDetected(this);
    }
}

void Bullet::StopFire() {
    isFired = false;
    position = Vector2(-20, -20);
}
