//
// Created by Juscelino Tanaka on 18/03/18.
//

#include "Ghost.h"
#include "GameManager.h"

Ghost::Ghost(const char * name) : SceneObject(name) {
    enableCollision = true;
    tickUpdate = true;

    // 8 cells per second * 16 pixels per cell
    velocity = Vector2(8 * 16 * 2, 0);

    // switch it to start going to left
    ToggleLeftRight();
}

void Ghost::Update() {

    position = position + velocity * Time::deltaTime;

    if (alignToPrevious) {
        alignToPrevious = false;

        auto previousGhost = GameManager::GetPreviousGhost(this);

        if (previousGhost != nullptr) {
            int xPos, yPos;

//            L::d("fixing %s with %s", name, previousGhost->name);

            // place right behind the previous ghost on list
            xPos = (int) Math::clamp(previousGhost->position.x + ((movingRight ? -1 : 1) * 16), 0, 29*16);

            position.x = xPos;
        }
    }


    if (position.y < 0 || position.y >= CoreEngine::getScreenSize().y) {
        ToggleUpDown();
        // make it move back to the last line (up or down)
        MoveToNextLine();
        // make it move to the next line (otherwise it will just come back on the same line)
        MoveToNextLine();
    }
}

void Ghost::OnCollisionDetected(SceneObject *other) {
    if (other->isTag("Bullet")) {
        L::d("%s got hit", name);
        GameManager::GhostShot(position);
    } else if (other->isTag("Player")) {
        L::d("player dies to: %s", name);
    } else if (other->isTag("Mushroom") || other->isTag("Wall")) {
//        L::d("%s - hit: %s - x: %f <> %d - %d", name, other->name, position.x, (int)round(position.x / 16), movingRight);
        ToggleLeftRight();
        MoveToNextLine();
    }
}

void Ghost::ToggleLeftRight() {
    movingRight = !movingRight;
    velocity.x = -1 * velocity.x;
}

void Ghost::ToggleUpDown() {
    movingDown = !movingDown;
}

void Ghost::MoveToNextLine() {
    float xPos, yPos;

    alignToPrevious = true;

    auto currentColumn = (int)round(position.x / 16);
    currentColumn = (int) Math::clamp(currentColumn, 0, 29);

    xPos = currentColumn * 16;
    yPos = position.y + (movingDown ? 1 : -1) * 16;

    position.x = xPos;
    position.y = yPos;
}
