/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-7
** File description:
** Ray
*/

#include "core/Ray.hpp"

namespace RayTracer
{

    Ray::Ray(const Math::Point3D &origin, const Math::Vector3D &direction) : origin(origin), direction(direction) {}
}
