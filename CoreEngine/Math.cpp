//
// Created by Juscelino Tanaka on 16/03/18.
//

#include "Math.h"

double Math::Clamp(double x, double min, double max) {
    return std::max(min, std::min(x, max));
}
