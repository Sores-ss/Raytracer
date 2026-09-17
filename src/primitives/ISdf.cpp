/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-7
** File description:
** ISdf - Default normal implementation
*/

#include "primitives/ISdf.hpp"

namespace RayTracer
{
    Math::Vector3D ISdf::normal(const Math::Point3D &point) const
    {
        constexpr double h = 1e-5;
        
        double d0 = distance(point);
        double dx = distance(point + Math::Vector3D(h, 0, 0)) - d0;
        double dy = distance(point + Math::Vector3D(0, h, 0)) - d0;
        double dz = distance(point + Math::Vector3D(0, 0, h)) - d0;

        Math::Vector3D grad(dx / h, dy / h, dz / h);
        double len = grad.length();
        
        if (len < 1e-10)
            return Math::Vector3D(0, 1, 0);

        return grad / len;
    }
}
