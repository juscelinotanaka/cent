//
// Created by Juscelino Tanaka on 21/03/18.
//

#include <sstream>
#include "Vector2.h"

Vector2 Vector2::zero = Vector2(0,0);
Vector2 Vector2::one = Vector2(1,1);

Vector2::Vector2() = default;

Vector2::Vector2(int x, int y) {
    this->x = x;
    this->y = y;
}

const char *Vector2::toStr(int precision) {
    std::stringstream timeText;
    timeText.str( "" );
    timeText << "(" << x << ", " << y << ")";

    return timeText.str().c_str();
}
