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

    const char *toStr(int precision = 2);

    Vector2 operator * (const float f) { return {this->x * f, this->y * f}; }
    Vector2 operator / (const float f) { return {this->x / f, this->y / f}; }
    Vector2 operator += (const float f) { return {this->x + f, this->y + f}; }
    Vector2 operator -= (const float f) { return {this->x - f, this->y - f}; }
    Vector2 operator *= (const float f) { return {this->x * f, this->y * f}; }
    Vector2 operator + (const Vector2 v) { return {this->x + v.x, this->y + v.y}; }
    Vector2 operator - (const Vector2 v) { return {this->x - v.x, this->y - v.y}; }
    Vector2 operator += (const Vector2 v) { return {this->x + v.x, this->y + v.y}; }
};


#endif //CENT_VECTOR2_H
