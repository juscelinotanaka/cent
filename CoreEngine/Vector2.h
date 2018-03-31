//
// Created by Juscelino Tanaka on 21/03/18.
//

#ifndef CENT_VECTOR2INT_H
#define CENT_VECTOR2INT_H



class Vector2 {
public:
    Vector2();
    Vector2(int x, int y);
    int x, y;
    static Vector2 one;
    static Vector2 zero;

    static Vector2 lerp(Vector2 a, Vector2 b, float t);

    const char *toStr(int precision = 2);

    Vector2 withX(const int x) { return {x, this->y}; }
    Vector2 withY(const int y) { return {this->x, y}; }
    Vector2 withXplus(const int x) { return {this->x + x, this->y}; }
    Vector2 withYplus(const int y) { return {this->x, this->y + y}; }

    Vector2 operator * (const double f) { return {static_cast<int>(this->x * f), static_cast<int>(this->y * f)}; }
    Vector2 operator * (const int f) { return {this->x * f, this->y * f}; }
    Vector2 operator / (const int f) { return {this->x / f, this->y / f}; }
    Vector2 operator += (const int f) { return {this->x + f, this->y + f}; }
    Vector2 operator -= (const int f) { return {this->x - f, this->y - f}; }
    Vector2 operator *= (const int f) { return {this->x * f, this->y * f}; }
    Vector2 operator + (const Vector2 v) { return {this->x + v.x, this->y + v.y}; }
    Vector2 operator - (const Vector2 v) { return {this->x - v.x, this->y - v.y}; }
    Vector2 operator += (const Vector2 v) { return {this->x + v.x, this->y + v.y}; }
    bool operator == (const Vector2 v) { return this->x == v.x && this->y == v.y; }
    bool operator != (const Vector2 v) { return this->x != v.x || this->y != v.y; }
};


#endif //CENT_VECTOR2INT_H
