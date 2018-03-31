//
// Created by Juscelino Tanaka on 16/03/18.
//

#ifndef CENT_MATH_H
#define CENT_MATH_H

#include <algorithm>

class Math {
public:
    static double clamp(double x, double min, double max);
    static int signal(int left);
    static double lerp(float a, float b, float t);
};


#endif //CENT_MATH_H
