#include "primitives/Cylinder.hpp"

#include <cmath>

namespace RayTracer {

static const double CYL_DEG = 3.14159265358979323846 / 180.0;

Cylinder::Cylinder(const Math::Point3D &origin, double radius,
                   const Math::Vector3D &axis, const Math::Vector3D &color)
    : APrimitive(origin, color), _radius(radius), _axis(axis.normalize()) {}

bool Cylinder::hits(const Ray &ray, double &t) const {
    Math::Vector3D oc = ray.origin - _origin;
    Math::Vector3D dperp = ray.direction - _axis * ray.direction.dot(_axis);
    Math::Vector3D ocperp = oc - _axis * oc.dot(_axis);

    double a = dperp.dot(dperp);
    double b = 2.0 * dperp.dot(ocperp);
    double c = ocperp.dot(ocperp) - _radius * _radius;
    double disc = b * b - 4.0 * a * c;
    if (disc < 0)
        return false;
    double sqrtd = std::sqrt(disc);
    double t0 = (-b - sqrtd) / (2.0 * a);
    double t1 = (-b + sqrtd) / (2.0 * a);
    if (t0 > 1e-6) { t = t0; return true; }
    if (t1 > 1e-6) { t = t1; return true; }
    return false;
}

Math::Vector3D Cylinder::getNormalAt(const Math::Point3D &point) const {
    Math::Vector3D v = point - _origin;
    Math::Point3D proj = _origin + _axis * v.dot(_axis);
    return (point - proj).normalize();
}

void Cylinder::rotateX(double deg) {
    APrimitive::rotateX(deg);
    double rad = deg * CYL_DEG;
    double c = std::cos(rad), s = std::sin(rad);
    double ny = _axis.y * c - _axis.z * s;
    double nz = _axis.y * s + _axis.z * c;
    _axis = Math::Vector3D(_axis.x, ny, nz).normalize();
}

void Cylinder::rotateY(double deg) {
    APrimitive::rotateY(deg);
    double rad = deg * CYL_DEG;
    double c = std::cos(rad), s = std::sin(rad);
    double nx = _axis.x * c + _axis.z * s;
    double nz = -_axis.x * s + _axis.z * c;
    _axis = Math::Vector3D(nx, _axis.y, nz).normalize();
}

void Cylinder::rotateZ(double deg) {
    APrimitive::rotateZ(deg);
    double rad = deg * CYL_DEG;
    double c = std::cos(rad), s = std::sin(rad);
    double nx = _axis.x * c - _axis.y * s;
    double ny = _axis.x * s + _axis.y * c;
    _axis = Math::Vector3D(nx, ny, _axis.z).normalize();
}

}
