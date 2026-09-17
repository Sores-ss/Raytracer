/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-7
** File description:
** Cone
*/

#include "primitives/Cone.hpp"

#include <cmath>

namespace RayTracer
{
    static const double CONE_PI  = 3.14159265358979323846;
    static const double CONE_DEG = CONE_PI / 180.0;

    Cone::Cone(const Math::Point3D &apex, double angleDeg, const Math::Vector3D &axis, const Math::Vector3D &color) : APrimitive(apex, color), _angle(angleDeg * CONE_DEG), _axis(axis.normalize()) 
    {
    }

    bool Cone::hits(const Ray &ray, double &t) const
    {
        double k;
        double dda;
        double oca;
        double a;
        double bhalf;
        double c;
        double disc;
        double sqrtd;
        double t0;
        double t1;
        Math::Vector3D oc = ray.origin - _origin;

        k = std::cos(_angle) * std::cos(_angle);
        dda = ray.direction.dot(_axis);
        oca = oc.dot(_axis);
        a = dda * dda - k * ray.direction.dot(ray.direction);
        bhalf = oca * dda - k * oc.dot(ray.direction);
        c = oca * oca - k * oc.dot(oc);
        if (std::abs(a) < 1e-9)
            return false;
        disc = bhalf * bhalf - a * c;
        if (disc < 0)
            return false;
        sqrtd = std::sqrt(disc);
        t0 = (-bhalf - sqrtd) / a;
        t1 = (-bhalf + sqrtd) / a;
        if (t0 > 1e-6){
            t = t0;
            return true;
        }
        if (t1 > 1e-6){
            t = t1;
            return true;
        }
        return false;
    }

    Math::Vector3D Cone::getNormalAt(const Math::Point3D &point) const
    {
        double k;
        Math::Vector3D v = point - _origin;

        k = std::cos(_angle) * std::cos(_angle);
        return (_axis * v.dot(_axis) - v * k).normalize();
    }

    void Cone::rotateX(double deg)
    {
        double rad;
        double c;
        double s;
        double ny;
        double nz;
        APrimitive::rotateX(deg);

        rad = deg * CONE_DEG;
        c = std::cos(rad);
        s = std::sin(rad);
        ny = _axis.y * c - _axis.z * s;
        nz = _axis.y * s + _axis.z * c;
        _axis = Math::Vector3D(_axis.x, ny, nz).normalize();
    }

    void Cone::rotateY(double deg)
    {
        double rad;
        double c;
        double s;
        double nx;
        double nz;
        APrimitive::rotateY(deg);

        rad = deg * CONE_DEG;
        c = std::cos(rad);
        s = std::sin(rad);
        nx = _axis.x * c + _axis.z * s;
        nz = -_axis.x * s + _axis.z * c;
        _axis = Math::Vector3D(nx, _axis.y, nz).normalize();
    }

    void Cone::rotateZ(double deg)
    {
        double rad;
        double c;
        double s;
        double nx;
        double ny;
        APrimitive::rotateZ(deg);

        rad = deg * CONE_DEG;
        c = std::cos(rad);
        s = std::sin(rad);
        nx = _axis.x * c - _axis.y * s;
        ny = _axis.x * s + _axis.y * c;
        _axis = Math::Vector3D(nx, ny, _axis.z).normalize();
    }
}
