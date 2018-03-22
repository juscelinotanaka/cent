//
// Created by Juscelino Tanaka on 21/03/18.
//

#include <sstream>
#include "Vector2int.h"

Vector2int Vector2int::zero = Vector2int(0,0);
Vector2int Vector2int::one = Vector2int(1,1);

Vector2int::Vector2int() = default;

Vector2int::Vector2int(int x, int y) {
    this->x = x;
    this->y = y;
}

const char *Vector2int::toStr(int precision) {
    std::stringstream timeText;
    timeText.str( "" );
    timeText << "(" << x << ", " << y << ")";

    return timeText.str().c_str();
}
