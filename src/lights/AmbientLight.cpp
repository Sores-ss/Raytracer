/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-7
** File description:
** AmbientLight
*/

#include "lights/AmbientLight.hpp"

namespace RayTracer
{
    AmbientLight::AmbientLight(double intensity, Math::Vector3D color) : ALight(intensity, color)
    {
    }

    Math::Vector3D AmbientLight::illuminate(const Math::Point3D &, const Math::Vector3D &) const
    {
        return _color * _intensity;
    }
}
