//
// Created by Juscelino Tanaka on 16/03/18.
//

#include "Math.h"

double Math::clamp(double x, double min, double max) {
    return std::max(min, std::min(x, max));
}

int Math::Signal(int number) {
    return number < 0 ? -1 : 1;
}
