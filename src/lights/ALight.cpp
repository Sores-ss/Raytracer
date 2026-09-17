/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-7
** File description:
** ALight
*/

#include "lights/ALight.hpp"

#include <limits>

namespace RayTracer
{
    ALight::ALight(double intensity, Math::Vector3D color) : _intensity(intensity), _color(color)
    {
    }

    Math::Vector3D ALight::shadowDir(const Math::Point3D &) const
    {
        return Math::Vector3D(0, 0, 0);
    }

    double ALight::shadowMaxDistance(const Math::Point3D &) const
    {
        return std::numeric_limits<double>::infinity();
    }
}
