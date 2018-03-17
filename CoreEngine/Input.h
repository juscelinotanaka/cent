//
// Created by Juscelino Tanaka on 15/03/18.
//

#ifndef CENT_INPUT_H
#define CENT_INPUT_H

#include "Vector2.h"

class Input {

public:
    static bool GetMouseDown();
    static bool GetMousePressed();
    static bool GetMouseUp();
    static bool Quit();
    static void HandleEvents();
    static Vector2 mousePosition;

    static bool GetEscape();
};


#endif //CENT_INPUT_H
