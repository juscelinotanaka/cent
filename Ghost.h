//
// Created by Juscelino Tanaka on 18/03/18.
//

#ifndef CENT_GHOST_H
#define CENT_GHOST_H


#include "CoreEngine/CoreEngine.h"
#include <vector>

class Ghost: public SceneObject {
public:
    explicit Ghost(const char * name);

    void Update() override;
    void OnCollisionDetected(SceneObject *other) override;

    void toggleLeftRight();
    void toggleUpDown();
    void toggleHorizontal();
    void resetGhost();
    void setHead();

    std::vector<Vector2> turnStack;
    bool hasTurnStack();
    Vector2 turnTop();
    bool invertNextHorizontal = false;

private:
    bool alignToPrevious = false;
    bool isHead = false;
    bool horizontal = true;
    bool movingLeft = true;
    bool movingDown = true;
    int speedMultiplier = 1;
    void AddTurnPosition(Vector2 pos, bool includeHead = false);
    void hitOnPos(Vector2 objPos);
    bool IgnoreMushroomPosition(Vector2 pos);
    Vector2 ignorePos;
    Vector2 previousHead;

    void RemoveTurnPositionFromTail(Vector2 pos);
};


#endif //CENT_GHOST_H
