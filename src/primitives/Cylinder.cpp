/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-7
** File description:
** Cylinder
*/

#include "primitives/Cylinder.hpp"

#include <algorithm>
#include <cmath>

namespace RayTracer
{

    static const double CYL_DEG = 3.14159265358979323846 / 180.0;

    static double absAverage(const Math::Vector3D &factors)
    {
        return (std::abs(factors.x) + std::abs(factors.y) + std::abs(factors.z)) / 3.0;
    }

    Cylinder::Cylinder(const Math::Point3D &origin, double radius, const Math::Vector3D &axis, const Math::Vector3D &color) : APrimitive(origin, color), _radius(radius), _axis(axis.normalize()) 
    {
    }

    bool Cylinder::hits(const Ray &ray, double &t) const
    {
        double a;
        double b;
        double c;
        double disc;
        double sqrtd;
        double t0;
        double t1;
        Math::Vector3D oc = ray.origin - _origin;
        Math::Vector3D dperp = ray.direction - _axis * ray.direction.dot(_axis);
        Math::Vector3D ocperp = oc - _axis * oc.dot(_axis);

        a = dperp.dot(dperp);
        b = 2.0 * dperp.dot(ocperp);
        c = ocperp.dot(ocperp) - _radius * _radius;
        disc = b * b - 4.0 * a * c;
        if (disc < 0)
            return false;
        sqrtd = std::sqrt(disc);
        t0 = (-b - sqrtd) / (2.0 * a);
        t1 = (-b + sqrtd) / (2.0 * a);
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

    Math::Vector3D Cylinder::getNormalAt(const Math::Point3D &point) const
    {
        Math::Vector3D v = point - _origin;
        Math::Point3D proj = _origin + _axis * v.dot(_axis);
        return (point - proj).normalize();
    }

    void Cylinder::scale(const Math::Vector3D &factors)
    {
        APrimitive::scale(factors);
        _radius *= std::max(0.01, absAverage(factors));
    }

    void Cylinder::rotateX(double deg)
    {
        double rad;
        double c;
        double s;
        double ny;
        double nz;
        APrimitive::rotateX(deg);

        rad = deg * CYL_DEG;
        c = std::cos(rad);
        s = std::sin(rad);
        ny = _axis.y * c - _axis.z * s;
        nz = _axis.y * s + _axis.z * c;
        _axis = Math::Vector3D(_axis.x, ny, nz).normalize();
    }

    void Cylinder::rotateY(double deg)
    {
        double rad;
        double c;
        double s;
        double nx;
        double nz;
        APrimitive::rotateY(deg);

        rad = deg * CYL_DEG;
        c = std::cos(rad);
        s = std::sin(rad);
        nx = _axis.x * c + _axis.z * s;
        nz = -_axis.x * s + _axis.z * c;
        _axis = Math::Vector3D(nx, _axis.y, nz).normalize();
    }

    void Cylinder::rotateZ(double deg)
    {
        double rad;
        double c;
        double s;
        double nx;
        double ny;
        APrimitive::rotateZ(deg);

        rad = deg * CYL_DEG;
        c = std::cos(rad);
        s = std::sin(rad);
        nx = _axis.x * c - _axis.y * s;
        ny = _axis.x * s + _axis.y * c;
        _axis = Math::Vector3D(nx, ny, _axis.z).normalize();
    }
}
