/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-7
** File description:
** Triangle - Möller–Trumbore ray-triangle intersection
*/

#include "primitives/Triangle.hpp"

#include <cmath>

namespace RayTracer
{
    static constexpr double EPSILON = 1e-8;

    Triangle::Triangle(const Math::Point3D &v0, const Math::Point3D &v1, const Math::Point3D &v2,
                       const Math::Vector3D &color)
        : APrimitive(v0, color), _v1(v1), _v2(v2)
    {
        _normal = computeNormal();
    }

    Math::Vector3D Triangle::computeNormal() const
    {
        Math::Vector3D edge1 = _v1 - _origin;
        Math::Vector3D edge2 = _v2 - _origin;
        
        Math::Vector3D normal(
            edge1.y * edge2.z - edge1.z * edge2.y,
            edge1.z * edge2.x - edge1.x * edge2.z,
            edge1.x * edge2.y - edge1.y * edge2.x
        );
        
        double len = normal.length();
        if (len < EPSILON)
            return Math::Vector3D(0, 1, 0);
        return normal / len;
    }

    bool Triangle::hits(const Ray &ray, double &t) const
    {
        Math::Vector3D edge1 = _v1 - _origin;
        Math::Vector3D edge2 = _v2 - _origin;
        
        Math::Vector3D h(
            ray.direction.y * edge2.z - ray.direction.z * edge2.y,
            ray.direction.z * edge2.x - ray.direction.x * edge2.z,
            ray.direction.x * edge2.y - ray.direction.y * edge2.x
        );
        
        double a = edge1.dot(h);
        
        if (std::abs(a) < EPSILON)
            return false;
        
        double f = 1.0 / a;
        Math::Vector3D s = ray.origin - _origin;
        double u = f * s.dot(h);
        
        if (u < 0.0 || u > 1.0)
            return false;
        
        Math::Vector3D q(
            s.y * edge1.z - s.z * edge1.y,
            s.z * edge1.x - s.x * edge1.z,
            s.x * edge1.y - s.y * edge1.x
        );
        
        double v = f * ray.direction.dot(q);
        
        if (v < 0.0 || u + v > 1.0)
            return false;
        
        double tCand = f * edge2.dot(q);
        
        if (tCand > 1e-6)
        {
            t = tCand;
            return true;
        }
        
        return false;
    }

    Math::Vector3D Triangle::getNormalAt(const Math::Point3D &) const
    {
        return _normal;
    }

    void Triangle::translate(const Math::Vector3D &offset)
    {
        APrimitive::translate(offset);
        _v1 = _v1 + offset;
        _v2 = _v2 + offset;
    }
}
