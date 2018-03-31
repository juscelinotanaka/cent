//
// Created by Juscelino Tanaka on 18/03/18.
//

#include "Ghost.h"
#include "GameManager.h"

Ghost::Ghost(const char * name) : SceneObject(name) {
    enableCollision = true;
    tickUpdate = true;
}

int tickSteps = 7;

void Ghost::Update() {
    // update behavior accordingly with the current state
    if (tickCount % tickSteps == 0) {
        tickCount = 0; // reset count

        previousPos = fromPos;
        fromPos = toPos;
        if (isHead) {
            toPos = getNextHeadPos();
        } else {
            auto prev = GameManager::getPreviousGhost(this);
            if (prev != nullptr) {
                toPos = prev->fromPos;
            }
        }
    }

    auto realPos = Vector2::lerp(fromPos * 16, toPos * 16, (float)tickCount / tickSteps);

    position = realPos;
    tickCount++;
}

void Ghost::OnCollisionDetected(SceneObject *other) {

    if (other->isTag("Bullet")) {
        // ghost is hit by a bullet
        GameManager::GhostShot(this);

    } else if (other->isTag("Player")) {
        // ghost hits player
        GameManager::PlayerDies();

    }
}

void Ghost::toggleHorizontal() {
    horizontal = !horizontal;
//    L::d("%s - new direc: %s", name, (horizontal ? "horizontal" : "vertical"));
}

void Ghost::toggleLeftRight() {
    movingLeft = !movingLeft;
//    L::d("%s - turning to: %s", name, (movingLeft ? "left" : "right"));
}

void Ghost::toggleUpDown() {
    movingDown = !movingDown;
//    L::d("%s - moving: %s", name, (movingDown ? "down" : "up"));
}

void Ghost::resetGhost() {
    enable = true;
    setImageFromPool(0);
    isHead = false;
    horizontal = true;
    movingDown = true;
    movingLeft = true;
}

void Ghost::setHead() {
    isHead = true;
}

Vector2 Ghost::getNextHeadPos() {
    if (!horizontal) {
        toggleHorizontal();
        toggleLeftRight();
    }

    // calculate new pos
    auto newPos = fromPos.withXplus(horizontal ? (movingLeft ? -1 : 1) : 0).withYplus(!horizontal ? (movingDown ? 1 : -1) : 0);

    // if new pos goes off screen horizontally or hit mushroom move it up or down
    if (GameManager::hasMushroomAt(newPos) || newPos.x == -1  || newPos.x == 30) {
        toggleHorizontal();
        newPos = fromPos.withXplus(horizontal ? (movingLeft ? -1 : 1) : 0).withYplus(!horizontal ? (movingDown ? 1 : -1) : 0);
    }

    // if after moving up or down it goes off screen again, toggle up/down direction
    if (newPos.y == -1 || newPos.y == 30) {
        toggleUpDown();
        newPos = fromPos.withXplus(horizontal ? (movingLeft ? -1 : 1) : 0).withYplus(!horizontal ? (movingDown ? 1 : -1) : 0);
    }

    return newPos;
}

void Ghost::setStartPos(int x, int y) {
    fromPos = toPos = previousPos = Vector2(x, y);
    position = fromPos * 16;
    tickCount = 0;
}

void Ghost::setAsHead(Ghost *head) {
    setImageFromPool(1);
    isHead = true;
    if (head != nullptr) {
        horizontal = head->horizontal;
        movingLeft = head->movingLeft;
        movingDown = head->movingDown;
    }
}

bool Ghost::IsHead() {
    return isHead;
}
