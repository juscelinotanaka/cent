//
// Created by Juscelino Tanaka on 16/03/18.
//

#include "Math.h"

double Math::clamp(double x, double min, double max) {
    return std::max(min, std::min(x, max));
}

int Math::signal(int number) {
    return number < 0 ? -1 : 1;
}

double Math::lerp(float a, float b, float t) {
    t = (float) clamp(t, 0, 1);
    return a + (b - a) * t;
}
