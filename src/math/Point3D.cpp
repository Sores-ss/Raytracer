#include "Point3D.hpp"

namespace Math {

Point3D::Point3D() : x(0), y(0), z(0) {}
Point3D::Point3D(double x, double y, double z) : x(x), y(y), z(z) {}

Point3D Point3D::operator+(const Vector3D &v) const {
    return {x + v.x, y + v.y, z + v.z};
}

Vector3D Point3D::operator-(const Point3D &other) const {
    return {x - other.x, y - other.y, z - other.z};
}

}
