/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-7
** File description:
** Plane
*/

#include "primitives/Plane.hpp"

#include <cmath>

namespace RayTracer
{
    Plane::Plane(const Math::Point3D &origin, const Math::Vector3D &normal, const Math::Vector3D &color) : APrimitive(origin, color), _normal(normal.normalize()) {}

    bool Plane::hits(const Ray &ray, double &t) const
    {
        double denom;

        denom = ray.direction.dot(_normal);
        if (std::abs(denom) < 1e-6)
            return false;
        Math::Vector3D diff = _origin - ray.origin;
        t = diff.dot(_normal) / denom;
        return t > 1e-6;
    }

    Math::Vector3D Plane::getNormalAt(const Math::Point3D &) const
    {
        return _normal;
    }

}
