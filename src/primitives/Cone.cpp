#include "primitives/Cone.hpp"

#include <cmath>

namespace RayTracer {

static const double CONE_PI  = 3.14159265358979323846;
static const double CONE_DEG = CONE_PI / 180.0;

Cone::Cone(const Math::Point3D &apex, double angleDeg,
           const Math::Vector3D &axis, const Math::Vector3D &color)
    : APrimitive(apex, color), _angle(angleDeg * CONE_DEG), _axis(axis.normalize()) {}

bool Cone::hits(const Ray &ray, double &t) const {
    Math::Vector3D oc = ray.origin - _origin;
    double k = std::cos(_angle) * std::cos(_angle);
    double dda = ray.direction.dot(_axis);
    double oca = oc.dot(_axis);

    double a = dda * dda - k * ray.direction.dot(ray.direction);
    double bhalf = oca * dda - k * oc.dot(ray.direction);
    double c = oca * oca - k * oc.dot(oc);

    if (std::abs(a) < 1e-9)
        return false;
    double disc = bhalf * bhalf - a * c;
    if (disc < 0)
        return false;
    double sqrtd = std::sqrt(disc);
    double t0 = (-bhalf - sqrtd) / a;
    double t1 = (-bhalf + sqrtd) / a;
    if (t0 > 1e-6) { t = t0; return true; }
    if (t1 > 1e-6) { t = t1; return true; }
    return false;
}

Math::Vector3D Cone::getNormalAt(const Math::Point3D &point) const {
    Math::Vector3D v = point - _origin;
    double k = std::cos(_angle) * std::cos(_angle);
    return (_axis * v.dot(_axis) - v * k).normalize();
}

void Cone::rotateX(double deg) {
    APrimitive::rotateX(deg);
    double rad = deg * CONE_DEG;
    double c = std::cos(rad), s = std::sin(rad);
    double ny = _axis.y * c - _axis.z * s;
    double nz = _axis.y * s + _axis.z * c;
    _axis = Math::Vector3D(_axis.x, ny, nz).normalize();
}

void Cone::rotateY(double deg) {
    APrimitive::rotateY(deg);
    double rad = deg * CONE_DEG;
    double c = std::cos(rad), s = std::sin(rad);
    double nx = _axis.x * c + _axis.z * s;
    double nz = -_axis.x * s + _axis.z * c;
    _axis = Math::Vector3D(nx, _axis.y, nz).normalize();
}

void Cone::rotateZ(double deg) {
    APrimitive::rotateZ(deg);
    double rad = deg * CONE_DEG;
    double c = std::cos(rad), s = std::sin(rad);
    double nx = _axis.x * c - _axis.y * s;
    double ny = _axis.x * s + _axis.y * c;
    _axis = Math::Vector3D(nx, ny, _axis.z).normalize();
}

}
