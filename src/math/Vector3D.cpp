#include "Vector3D.hpp"

#include <cmath>

namespace Math {

Vector3D::Vector3D() : x(0), y(0), z(0) {}
Vector3D::Vector3D(double x, double y, double z) : x(x), y(y), z(z) {}

double Vector3D::length() const {
    return std::sqrt(x * x + y * y + z * z);
}

double Vector3D::dot(const Vector3D &v) const {
    return x * v.x + y * v.y + z * v.z;
}

Vector3D Vector3D::normalize() const {
    return *this / length();
}

Vector3D Vector3D::operator+(const Vector3D &v) const { return {x + v.x, y + v.y, z + v.z}; }
Vector3D Vector3D::operator-(const Vector3D &v) const { return {x - v.x, y - v.y, z - v.z}; }
Vector3D Vector3D::operator*(const Vector3D &v) const { return {x * v.x, y * v.y, z * v.z}; }
Vector3D Vector3D::operator/(const Vector3D &v) const { return {x / v.x, y / v.y, z / v.z}; }

Vector3D Vector3D::operator*(double t) const { return {x * t, y * t, z * t}; }
Vector3D Vector3D::operator/(double t) const { return {x / t, y / t, z / t}; }

Vector3D &Vector3D::operator+=(const Vector3D &v) { x += v.x; y += v.y; z += v.z; return *this; }
Vector3D &Vector3D::operator-=(const Vector3D &v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
Vector3D &Vector3D::operator*=(const Vector3D &v) { x *= v.x; y *= v.y; z *= v.z; return *this; }
Vector3D &Vector3D::operator/=(const Vector3D &v) { x /= v.x; y /= v.y; z /= v.z; return *this; }

Vector3D &Vector3D::operator*=(double t) { x *= t; y *= t; z *= t; return *this; }
Vector3D &Vector3D::operator/=(double t) { x /= t; y /= t; z /= t; return *this; }

}
