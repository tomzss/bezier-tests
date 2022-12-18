#include "Vector.hpp"

#include <cmath>

void Vector::setX(float arg) {
    x = arg;
}

void Vector::setY(float arg) {
    y = arg;
}

float Vector::getX() const {
    return x;
}

float Vector::getY() const {
    return y;
}

float Vector::getLength() const {
    return std::sqrt(std::pow(x, 2.f) + std::pow(y, 2.f));
}

Vector Vector::operator+(const Vector &other) const {
    return {x + other.x, y + other.y};
}

void Vector::operator+=(const Vector &other) {
    *this = *this + other;
}

Vector Vector::operator-(const Vector &other) const {
    return {x - other.x, y - other.y};
}

void Vector::operator-=(const Vector &other) {
    *this = *this - other;
}

Vector::Vector(float x, float y) :
        x(x),
        y(y) {}
