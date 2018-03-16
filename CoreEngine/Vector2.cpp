//
// Created by Juscelino Tanaka on 15/03/18.
//

#include <string>
#include <sstream>
#include <iomanip>
#include "Vector2.h"

Vector2 Vector2::one = Vector2(1, 1);
Vector2 Vector2::zero = Vector2(0, 0);

Vector2::Vector2(float x, float y) : x(x), y(y) {}

Vector2::Vector2() {}

const char * Vector2::toStr(int precision) {
    std::stringstream timeText;
    timeText.str( "" );
    timeText << "(" << x << ", " << y << ")";

    return timeText.str().c_str();
}
