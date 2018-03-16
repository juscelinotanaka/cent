//
// Created by Juscelino Tanaka on 15/03/18.
//

#ifndef CENT_VECTOR2_H
#define CENT_VECTOR2_H


class Vector2 {
public:
    Vector2();
    Vector2(float x, float y);
    float x, y;
    static Vector2 one;
    static Vector2 zero;

    Vector2 operator * (const float f) {
        return {this->x * f, this->y * f};
    }

    const char *toStr(int precision = 2);
};


#endif //CENT_VECTOR2_H
