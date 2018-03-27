//
// Created by Juscelino Tanaka on 18/03/18.
//

#ifndef CENT_GHOST_H
#define CENT_GHOST_H


#include "CoreEngine/CoreEngine.h"
#include <stack>

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

    std::stack<Vector2> hitStack;
    bool hasHitStack();
    Vector2 hitTop();

private:
    bool alignToPrevious = false;
    bool isHead = false;
    bool horizontal = false;
    bool movingRight = true;
    bool movingDown = true;
    int speedMultiplier = 1;

    void AddHitToTail(Vector2 pos, bool includeHead);

    void toggleHit(Vector2 objPos);

    bool waitingToPop;
};


#endif //CENT_GHOST_H
