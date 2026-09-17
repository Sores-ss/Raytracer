#include "primitives/APrimitive.hpp"

#include <cmath>

namespace RayTracer {

static const double APDEG = 3.14159265358979323846 / 180.0;

APrimitive::APrimitive(const Math::Point3D &origin, const Math::Vector3D &color)
    : _origin(origin), _color(color) {}

Math::Vector3D APrimitive::getColor() const {
    return _color;
}

void APrimitive::translate(const Math::Vector3D &offset) {
    _origin = _origin + offset;
}

void APrimitive::rotateX(double deg) {
    double rad = deg * APDEG;
    double c = std::cos(rad), s = std::sin(rad);
    double ny = _origin.y * c - _origin.z * s;
    double nz = _origin.y * s + _origin.z * c;
    _origin = Math::Point3D(_origin.x, ny, nz);
}

void APrimitive::rotateY(double deg) {
    double rad = deg * APDEG;
    double c = std::cos(rad), s = std::sin(rad);
    double nx = _origin.x * c + _origin.z * s;
    double nz = -_origin.x * s + _origin.z * c;
    _origin = Math::Point3D(nx, _origin.y, nz);
}

void APrimitive::rotateZ(double deg) {
    double rad = deg * APDEG;
    double c = std::cos(rad), s = std::sin(rad);
    double nx = _origin.x * c - _origin.y * s;
    double ny = _origin.x * s + _origin.y * c;
    _origin = Math::Point3D(nx, ny, _origin.z);
}

}
