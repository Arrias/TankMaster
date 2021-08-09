#include "Vector.h"
#include "../general_functions/general_functions.h"

Vector::Vector(float x, float y) : x(x), y(y) {}

Vector::Vector(sf::Vector2f vec) : x(vec.x), y(vec.y) {}

sf::Vector2f Vector::to_sfml_vector() const {
    return sf::Vector2f(x, y);
}

float Vector::scalar_prod(Vector oth) {
    return x * oth.x + y * oth.y;
}

float Vector::vec_prod(Vector oth) {
    return x * oth.y - oth.x * y;
}

Vector Vector::normalize() {
    return Vector(x / len(), y / len());
}

float Vector::polar() {
    float res = atan2(y, x);
    if (res < 0)
        res += 2 * PI;
    return res;
}

Vector Vector::rotate(float angle) {
    angle = deg_to_rad(angle);
    Vector ret;
    ret.x = x * cos(angle) - y * sin(angle);
    ret.y = x * sin(angle) + y * cos(angle);
    return ret;
}

float Vector::len() {
    return sqrt(x * x + y * y);
}

bool Vector::operator==(Vector oth) {
    return is_equal(x, oth.x) && is_equal(y, oth.y);
}

Vector Vector::operator+(Vector oth) {
    return Vector(x + oth.x, y + oth.y);
}

Vector Vector::operator-(Vector oth) {
    return *this + (oth * (-1));
}

Vector Vector::operator*(float scalar) {
    return Vector(x * scalar, y * scalar);
}

void Vector::operator+=(Vector oth) {
    *this = *this + oth;
}

void Vector::operator-=(Vector oth) {
    *this = *this - oth;
}

void Vector::operator*=(float scalar) {
    *this = *this * scalar;
}

float Vector::angle_angle_between(Vector oth) {
    float a1 = polar(), a2 = oth.polar();
    float res = a1 - a2;
    if (res > PI)
        res -= 2 * PI;
    else if (res < -PI)
        res += 2 * PI;
    return rad_to_deg(-res);
}
