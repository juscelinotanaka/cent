//
// Created by Juscelino Tanaka on 18/03/18.
//

#ifndef CENT_GHOST_H
#define CENT_GHOST_H


#include "CoreEngine/CoreEngine.h"

class Ghost: public SceneObject {
public:
    explicit Ghost(const char * name);

    void Update() override;
    void OnCollisionDetected(SceneObject *other) override;

    void toggleLeftRight();
    void toggleUpDown();
    void moveToNextLine();
    void resetGhost();
    bool alignToPrevious = false;

private:
    bool movingRight = true;
    bool movingDown = true;

};


#endif //CENT_GHOST_H
