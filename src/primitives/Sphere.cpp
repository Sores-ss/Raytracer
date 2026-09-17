#include "primitives/Sphere.hpp"

#include <cmath>

namespace RayTracer {

Sphere::Sphere(const Math::Point3D &center, double radius, const Math::Vector3D &color)
    : APrimitive(center, color), _radius(radius) {}

bool Sphere::hits(const Ray &ray, double &t) const {
    Math::Vector3D oc = ray.origin - _origin;
    // Quadratic: a*t^2 + b*t + c = 0
    double a = ray.direction.dot(ray.direction);
    double b = 2.0 * oc.dot(ray.direction);
    double c = oc.dot(oc) - _radius * _radius;
    double d = b * b - 4 * a * c;
    if (d < 0)
        return false;
    double sqrtd = std::sqrt(d);
    double t0 = (-b - sqrtd) / (2 * a);
    double t1 = (-b + sqrtd) / (2 * a);
    if (t0 > 1e-6) { t = t0; return true; }
    if (t1 > 1e-6) { t = t1; return true; }
    return false;
}

Math::Vector3D Sphere::getNormalAt(const Math::Point3D &point) const {
    return (point - _origin).normalize();
}

}
