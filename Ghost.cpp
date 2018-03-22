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
        int topx = hitTop().x;
        int topy = hitTop().y;
        auto cur = getGridPosition() * 16;

        bool equal = topx == cur.x && cur.y == topy;

//        L::d("%s -total: %d - topx: %d, %d - cur: %s",
//             name,
//             hitStack.size(),
//             topx,
//             topy,
//            cur.toStr());

        if (hitTop() == (getGridPosition() * 16)) {
            toggleHit();
            hitStack.pop();
        }

    }


//    if (position.y < 0 || position.y >= CoreEngine::getScreenSize().y) {
//        toggleUpDown();
//        // make it move back to the last line (up or down)
//        moveToNextLine();
//        // make it move to the next line (otherwise it will just come back on the same line)
//        moveToNextLine();
//    }
}

void Ghost::OnCollisionDetected(SceneObject *other) {
    if (other->isTag("Bullet")) {
        L::d("%s got hit", name);
        GameManager::GhostShot(this);
    } else if (other->isTag("Player")) {
//        L::d("player dies to: %s", name);
    } else if (other->isTag("Mushroom") || other->isTag("Wall")) {

        if (!isHead)
            return;

        if (dynamic_cast<Mushroom *>(other)) {

            auto m = dynamic_cast<Mushroom *>(other);

            L::d("%s hit: %s[%d] - at: %s hor: %d ", name, other->name, m->id, getGridPosition().toStr(), horizontal);
        } else {
            L::d("%s hit: %s - at: %s hor: %d", name, other->name, getGridPosition().toStr(), horizontal);
        }

        toggleHit();
    }
}

void Ghost::toggleHorizontal() {
    horizontal = !horizontal;
}

void Ghost::toggleLeftRight() {
    movingRight = !movingRight;
}

void Ghost::toggleUpDown() {
    movingDown = !movingDown;
}

//void Ghost::moveToNextLine() {
//    float xPos, yPos;
//
//    alignToPrevious = true;
//
//    auto currentColumn = (int)round(position.x / 16);
//    currentColumn = (int) Math::clamp(currentColumn, 0, 29);
//
//    xPos = currentColumn * 16;
//    yPos = position.y + (movingDown ? 1 : -1) * 16;
//
//    position.x = xPos;
//    position.y = yPos;
//}

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

Vector2int Ghost::hitTop() {
    return hitStack.top();
}

void Ghost::toggleHit() {
    toggleHorizontal();

    if (!horizontal) { // it is horizontal, but was just negated on the previous line

        // round to the right position - head always go one step further
        int currentXPos = (getGridPosition().x + (!movingRight && isHead ? 1 : 0)) * 16;
        int currentYPos = getGridPosition().y * 16;

        int nextYPos = (getGridPosition().y + (movingDown ? 1 : -1)) * 16;

        L::d("%s - current X: (%d,%d) - nextY: %d - hor: %d - down: %d", name, currentXPos, currentYPos, nextYPos, horizontal, movingDown);

        position.x = currentXPos;
        position.y = currentYPos;

        if (isHead) {
            AddHitToTail(Vector2int(currentXPos, nextYPos), true);
            AddHitToTail(Vector2int(currentXPos, currentYPos), false);
        }
    } else {
        toggleLeftRight();
    }




}

void Ghost::AddHitToTail(Vector2int pos, bool includeHead = false) {
    std::vector<Ghost *> tail = GameManager::getTailWithHead(this);
    for (int i = includeHead ? 0 : 1; i < tail.size(); ++i) {
        L::d("added %s to %s", pos.toStr(), tail[i]->name);
        tail[i]->hitStack.push(pos);
    }
}

