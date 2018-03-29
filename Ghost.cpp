//
// Created by Juscelino Tanaka on 18/03/18.
//

#include "Ghost.h"
#include "GameManager.h"

Ghost::Ghost(const char * name) : SceneObject(name) {
    enableCollision = true;
    tickUpdate = true;
}

void Ghost::hitOnPos(Vector2 objPos) {

    if (!isHead)
        return;



    if (horizontal) { // it is horizontal, but was just negated on the previous line

        // round to the right position - head always go one step further
        int tailTurnX = objPos.x + (movingLeft ? 0 : -1);
        int tailTurnY = getGridPosition().y;

        int nextLineTurnX = objPos.x + (movingLeft ? 1 : -1);
        int nextLineTurnY = (getGridPosition().y + (movingDown ? 1 : -1));

        L::d("%s - tail: (%d,%d) - nextLine: (%d,%d) - hor: %d - left: %d", name, tailTurnX, tailTurnY, nextLineTurnX,nextLineTurnY, horizontal, movingLeft);

        position.x = nextLineTurnX * 16;

        L::d("prev: %s", previousHead.toStr());
        L::d("obj: %s", objPos.toStr());
        if (previousHead == Vector2(tailTurnX, tailTurnY)) {
            RemoveTurnPositionFromTail(Vector2(tailTurnX, tailTurnY));
        } else {
            // set next turn to every part of the tail
            AddTurnPosition(Vector2(tailTurnX, tailTurnY), false);
        }

        // set next turn on next line for everybody - including head
        AddTurnPosition(Vector2(nextLineTurnX, nextLineTurnY), true);
    }

    toggleHorizontal();
}

void Ghost::Update() {
    // 8 cells per second * 16 pixels per cell
    auto speed = 8 * 16 * speedMultiplier;

    velocity.x = (movingLeft ? -1 : 1) * (horizontal ? speed : 0);
    velocity.y = (movingDown ? 1 : -1) * (!horizontal ? speed : 0);

    position = position + velocity * Time::deltaTime;

    if (isName("Ghost_1") && getGridPosition().y != 0) {
//        L::d("WTF: %s", getGridPosition().toStr());
    }

    if (hasTurnStack()) {
        if (turnTop() == getGridPosition()) {
            L::d("%s - got into: %s", name, turnTop().toStr());

            // realign itens to grid to avoid collision twice
            if (!isHead && horizontal)
                position.x = (getGridPosition().x + (movingLeft ? 1 : 0)) * 16;

            // ignores if more than one line
            if (!horizontal && !invertNextHorizontal) {
                toggleLeftRight();
            }

            if (!horizontal) {
                position.y = (turnTop().y) * 16;
                invertNextHorizontal = false;
            }

            toggleHorizontal();

            ignorePos = turnTop();
            L::d("%s - erasing: %s", name, turnTop().toStr());
            if (isHead)
                previousHead = turnTop();

            turnStack.erase(std::remove(turnStack.begin(), turnStack.end(), turnTop()), turnStack.end());

            if (hasTurnStack()) {
                L::d("%s - new Top: %s", name, turnTop().toStr());
            }
        }
    }

    if (isHead && (position.y < 0 || position.y >= CoreEngine::getScreenSize().y)) {
        toggleUpDown();
    }
}

void Ghost::OnCollisionDetected(SceneObject *other) {

    if (other->isTag("Bullet")) {
        // ghost is hit by a bullet
        GameManager::GhostShot(this);

    } else if (other->isTag("Player")) {
        // ghost hits player
        GameManager::PlayerDies();

    } else if (other->isTag("Mushroom")) {
        // ghost hits a mushroom
        if (!isHead
            || IgnoreMushroomPosition(other->getGridPosition())
            || (movingLeft && other->getGridPosition() != getGridPosition())) {
            return;
        }

        if (dynamic_cast<Mushroom *>(other)) {
            auto m = dynamic_cast<Mushroom *>(other);
            L::d("%s hit: %s[%d] - at: %s im: %s ", name, other->name, m->id, m->getGridPosition().toStr(), getGridPosition().toStr());
        }

        hitOnPos(other->getGridPosition());
    } else if (other->isTag("Wall")) {
        if (!isHead)
            return;

        L::d("%s hit: %s - at: %s hor: %d", name, other->name, getGridPosition().toStr(), horizontal);

        hitOnPos(other->getGridPosition());
    }
}

void Ghost::toggleHorizontal() {
    horizontal = !horizontal;
//    L::d("%s - new direc: %s", name, (horizontal ? "horizontal" : "vertical"));
}

void Ghost::toggleLeftRight() {
    movingLeft = !movingLeft;
//    L::d("%s - turning to: %s", name, (movingLeft ? "right" : "left"));
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

bool Ghost::hasTurnStack() {
    return turnStack.size() > 0;
}

Vector2 Ghost::turnTop() {
    return turnStack.front();
}

void Ghost::AddTurnPosition(Vector2 pos, bool includeHead) {
    std::vector<Ghost *> tail = GameManager::getTailWithHead(this);
    for (int i = includeHead ? 0 : 1; i < tail.size(); ++i) {
        tail[i]->turnStack.push_back(pos);
        L::d("added %s to %s", pos.toStr(), tail[i]->name);
    }
}

bool Ghost::IgnoreMushroomPosition(Vector2 pos) {
    return hasTurnStack() ? (turnTop() == pos || ignorePos == pos) :  ignorePos == pos;
}

void Ghost::RemoveTurnPositionFromTail(Vector2 pos) {
    std::vector<Ghost *> tail = GameManager::getTailWithHead(this);
    for (int i = 1; i < tail.size(); ++i) {
        L::d("removing: %d", tail[i]->turnStack.size());
        for (int j = 0; j < tail[i]->turnStack.size(); ++j) {
            if (tail[i]->turnStack[j] == pos) {
                tail[i]->turnStack.erase(std::remove(tail[i]->turnStack.begin(), tail[i]->turnStack.end(),
                                                     tail[i]->turnStack[j]), tail[i]->turnStack.end());
            }

        }

        tail[i]->invertNextHorizontal = !tail[i]->invertNextHorizontal;
        L::d("removed? %d", tail[i]->turnStack.size());
    }
}

