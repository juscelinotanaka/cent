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
    void hit();
    bool notUpdatedYet();

    std::vector<Vector2> turnStack;

    void setStartPos(int x, int y);
    Vector2 getFromPos () { return fromPos; }
    Vector2 getToPos () { return toPos; }
    Vector2 getPreviousPos () { return previousPos; }

private:
    bool isHead = false;
    bool horizontal = true;
    bool movingLeft = true;
    bool movingDown = true;
    int tickCount = 0;
    Vector2 fromPos, toPos, previousPos;

    Vector2 getNextHeadPos();
};


#endif //CENT_GHOST_H
