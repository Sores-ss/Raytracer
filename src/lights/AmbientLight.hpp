/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-7
** File description:
** AmbientLight
*/

#pragma once

#include "lights/ALight.hpp"
#include "math/Vector3D.hpp"

namespace RayTracer
{
    class AmbientLight : public ALight
    {
        public:
            AmbientLight(double intensity, Math::Vector3D color = Math::Vector3D(1, 1, 1));

            Math::Vector3D illuminate(const Math::Point3D &point, const Math::Vector3D &normal) const override;
    };
}
