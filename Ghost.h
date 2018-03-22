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
    void moveToNextLine();
    void resetGhost();
    void setHead();

    std::stack<Vector2int> hitStack;
    bool hasHitStack();
    Vector2int hitTop();

private:
    bool alignToPrevious = false;
    bool isHead = false;
    bool horizontal = false;
    bool movingRight = true;
    bool movingDown = true;
    int speedMultiplier = 1;

    void toggleHit();

    void AddHitToTail(Vector2int pos, bool includeHead);
};


#endif //CENT_GHOST_H
