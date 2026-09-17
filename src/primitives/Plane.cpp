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

    Math::Vector3D Plane::getColorAt(const Math::Point3D &point) const
    {
        if (!_hasCheckerboard)
            return _color;
        double ax = std::abs(_normal.x);
        double ay = std::abs(_normal.y);
        double az = std::abs(_normal.z);
        double u;
        double v;

        if (ax >= ay && ax >= az) {
            u = point.y;
            v = point.z;
        } else if (ay >= ax && ay >= az) {
            u = point.x;
            v = point.z;
        } else {
            u = point.x;
            v = point.y;
        }
        int cu = static_cast<int>(std::floor(u / _checkerCellSize));
        int cv = static_cast<int>(std::floor(v / _checkerCellSize));

        if (((cu + cv) & 1) == 0)
            return _color;
        return _checkerColor;
    }

}
