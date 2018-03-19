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

    void ToggleLeftRight();
    void ToggleUpDown();
    bool alignToPrevious = false;

private:
    bool movingRight = true;
    bool movingDown = true;

    void MoveToNextLine();
};


#endif //CENT_GHOST_H
