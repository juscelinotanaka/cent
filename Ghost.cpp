//
// Created by Juscelino Tanaka on 18/03/18.
//

#include "Ghost.h"
#include "GameManager.h"

Ghost::Ghost(const char * name) : SceneObject(name) {
    enableCollision = true;
    tickUpdate = true;

    toggleHorizontal();

    // switch it to start going to left
    toggleLeftRight();
}

void Ghost::Update() {
    // 8 cells per second * 16 pixels per cell
    auto speed = 8 * 16 * speedMultiplier;

    velocity.x = (movingRight ? 1 : -1) * (horizontal ? speed : 0);
    velocity.y = (movingDown ? 1 : -1) * (!horizontal ? speed : 0);

    position = position + velocity * Time::deltaTime;

//    if (alignToPrevious) {
//        alignToPrevious = false;
//
//        auto previousGhost = GameManager::GetPreviousGhost(this);
//
//        if (previousGhost != nullptr) {
//            int xPos, yPos;
//
////            L::d("fixing %s with %s", name, previousGhost->name);
//
//            // place right behind the previous ghost on list
//            xPos = (int) Math::clamp(previousGhost->position.x + ((movingRight ? -1 : 1) * 16), 0, 29*16);
//
//            position.x = xPos;
//        }
//    }

    if (hasHitStack()) {
        auto cur = getGridPosition() * 16;

        if (hitTop() == (getGridPosition() * 16)) {
            L::d("%s - got into: %s", name, hitTop().toStr());
            auto pos = getGridPosition();
            pos.x = pos.x + (movingRight ? 0 : 0);
            toggleHit(pos);
            hitStack.pop();
        }
    }

    if (isHead && (position.y < 0 || position.y >= CoreEngine::getScreenSize().y)) {
        toggleUpDown();
//        toggleHit();
//        toggleHit();
    }
}

void Ghost::OnCollisionDetected(SceneObject *other) {
    if (other->isTag("Bullet")) {
        L::d("%s got hit", name);
        GameManager::GhostShot(this);
    } else if (other->isTag("Player")) {
//        L::d("player dies to: %s", name);
    } else if (other->isTag("Mushroom") || other->isTag("Wall")) {

        if (!isHead
//            || (!hitStack.empty() && other->getGridPosition() * 16 == hitTop())
            || other->getGridPosition() != getGridPosition()
                ) {
//            L::d("returning: %s", other->getGridPosition().toStr());
//            L::d("::: %s", getGridPosition().toStr());
            return;
        }

        if (dynamic_cast<Mushroom *>(other)) {

            auto m = dynamic_cast<Mushroom *>(other);

            L::d("%s hit: %s[%d] - at: %s hor: %d ", name, other->name, m->id, getGridPosition().toStr(), horizontal);
        } else {
            L::d("%s hit: %s - at: %s hor: %d", name, other->name, getGridPosition().toStr(), horizontal);
        }

        toggleHit(other->getGridPosition());
    }
}

void Ghost::toggleHorizontal() {
    horizontal = !horizontal;
    L::d("%s - new direc: %s", name, (horizontal ? "horizontal" : "vertical"));
}

void Ghost::toggleLeftRight() {
    movingRight = !movingRight;
    L::d("%s - turning to: %s", name, (movingRight ? "right" : "left"));
}

void Ghost::toggleUpDown() {
    movingDown = !movingDown;
    L::d("%s - moving: %s", name, (movingDown ? "down" : "up"));
}

void Ghost::resetGhost() {
    enable = true;
    setImageFromPool(0);
    isHead = false;
    horizontal = true;
    movingDown = true;
    movingRight = true;
    toggleLeftRight();
}

void Ghost::setHead() {
    isHead = true;
}

bool Ghost::hasHitStack() {
    return hitStack.size() > 0;
}

Vector2 Ghost::hitTop() {
    return hitStack.top();
}

void Ghost::toggleHit(Vector2 objPos) {
    toggleHorizontal();

    if (!horizontal) { // it is horizontal, but was just negated on the previous line

        // round to the right position - head always go one step further
        int othersXPos = (objPos.x + (isHead && movingRight ? -1 : 1));
        int othersYPos = objPos.y;

        int nextYPos = (objPos.y + (movingDown ? 1 : -1));
        L::d("pos: %s", objPos.toStr());

        L::d("%s - current X: (%d,%d) - nextY: %d - hor: %d - down: %d", name, othersXPos, othersYPos, nextYPos, horizontal, movingDown);

        position.x = othersXPos * 16;

        if (isHead) {
            AddHitToTail(Vector2(othersXPos, nextYPos) * 16, true);
            AddHitToTail(Vector2(othersXPos, othersYPos) * 16, false);
        }
    } else {
        toggleLeftRight();
    }




}

void Ghost::AddHitToTail(Vector2 pos, bool includeHead = false) {
    std::vector<Ghost *> tail = GameManager::getTailWithHead(this);
    for (int i = includeHead ? 0 : 1; i < tail.size(); ++i) {
        L::d("added %s to %s", pos.toStr(), tail[i]->name);
        tail[i]->hitStack.push(pos);
    }
}

