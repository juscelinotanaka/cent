//
// Created by Juscelino Tanaka on 21/03/18.
//

#ifndef CENT_VECTOR2float_H
#define CENT_VECTOR2float_H



class Vector2 {
public:
    Vector2();
    Vector2(float x, float y);
    float x, y;
    static Vector2 one;
    static Vector2 zero;

    static Vector2 lerp(Vector2 a, Vector2 b, float t);

    const char *toStr(float precision = 2);

    Vector2 withX(const float x) { return {x, this->y}; }
    Vector2 withY(const float y) { return {this->x, y}; }
    Vector2 withXplus(const float x) { return {this->x + x, this->y}; }
    Vector2 withYplus(const float y) { return {this->x, this->y + y}; }

//    Vector2 operator * (const double f) { return {static_cast<float>(this->x * f), static_cast<float>(this->y * f)}; }
    Vector2 operator * (const float f) { return {this->x * f, this->y * f}; }
    Vector2 operator / (const float f) { return {this->x / f, this->y / f}; }
    Vector2 operator += (const float f) { return {this->x + f, this->y + f}; }
    Vector2 operator -= (const float f) { return {this->x - f, this->y - f}; }
    Vector2 operator *= (const float f) { return {this->x * f, this->y * f}; }
    Vector2 operator + (const Vector2 v) { return {this->x + v.x, this->y + v.y}; }
    Vector2 operator - (const Vector2 v) { return {this->x - v.x, this->y - v.y}; }
    Vector2 operator += (const Vector2 v) { return {this->x + v.x, this->y + v.y}; }
    bool operator == (const Vector2 v) { return this->x == v.x && this->y == v.y; }
    bool operator != (const Vector2 v) { return this->x != v.x || this->y != v.y; }
};


#endif //CENT_VECTOR2float_H
