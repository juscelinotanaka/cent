//
// Created by Juscelino Tanaka on 21/03/18.
//

#ifndef CENT_VECTOR2INT_H
#define CENT_VECTOR2INT_H



class Vector2int {
public:
    Vector2int();
    Vector2int(int x, int y);
    int x, y;
    static Vector2int one;
    static Vector2int zero;

    const char *toStr(int precision = 2);

    Vector2int operator * (const int f) { return {this->x * f, this->y * f}; }
    Vector2int operator / (const int f) { return {this->x / f, this->y / f}; }
    Vector2int operator += (const int f) { return {this->x + f, this->y + f}; }
    Vector2int operator -= (const int f) { return {this->x - f, this->y - f}; }
    Vector2int operator *= (const int f) { return {this->x * f, this->y * f}; }
    Vector2int operator + (const Vector2int v) { return {this->x + v.x, this->y + v.y}; }
    Vector2int operator - (const Vector2int v) { return {this->x - v.x, this->y - v.y}; }
    Vector2int operator += (const Vector2int v) { return {this->x + v.x, this->y + v.y}; }
    bool operator == (const Vector2int v) { return this->x == v.x && this->y == v.y; }
};


#endif //CENT_VECTOR2INT_H
