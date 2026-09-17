/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-7
** File description:
** Sphere
*/

#include "primitives/Sphere.hpp"

#include <algorithm>
#include <cmath>

namespace RayTracer
{

    static double absAverage(const Math::Vector3D &factors)
    {
        return (std::abs(factors.x) + std::abs(factors.y) + std::abs(factors.z)) / 3.0;
    }

    Sphere::Sphere(const Math::Point3D &center, double radius, const Math::Vector3D &color) : APrimitive(center, color), _radius(radius)
    {
    }

    bool Sphere::hits(const Ray &ray, double &t) const
    {
        double a;
        double b;
        double c;
        double d;
        double sqrtd;
        double t0;
        double t1;
        Math::Vector3D oc = ray.origin - _origin;

        a = ray.direction.dot(ray.direction);
        b = 2.0 * oc.dot(ray.direction);
        c = oc.dot(oc) - _radius * _radius;
        d = b * b - 4 * a * c;
        if (d < 0)
            return false;
        sqrtd = std::sqrt(d);
        t0 = (-b - sqrtd) / (2 * a);
        t1 = (-b + sqrtd) / (2 * a);
        if (t0 > 1e-6) {
            t = t0;
            return true;
        }
        if (t1 > 1e-6) {
            t = t1;
            return true;
        }
        return false;
    }

    Math::Vector3D Sphere::getNormalAt(const Math::Point3D &point) const
    {
        return (point - _origin).normalize();
    }

    void Sphere::scale(const Math::Vector3D &factors)
    {
        APrimitive::scale(factors);
        _radius *= std::max(0.01, absAverage(factors));
    }

}
