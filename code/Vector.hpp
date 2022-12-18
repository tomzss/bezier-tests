#pragma once

#include "utilities.hpp"

struct Vector {
public:
    Vector(float x, float y);

    void setX(float arg);
    void setY(float arg);

    ND float getX() const;
    ND float getY() const;
    ND float getLength() const;
    ND float getAngle() const;

    ND Vector operator+(Vector const &other) const;
    void operator+=(Vector const &other);

    ND Vector operator-(Vector const &other) const;
    void operator-=(Vector const &other);

private:
    float x;
    float y;
};
