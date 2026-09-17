/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-7
** File description:
** PointLight
*/

#pragma once

#include "lights/ALight.hpp"
#include "math/Point3D.hpp"

namespace RayTracer
{
    class PointLight : public ALight
    {
        public:
            PointLight(const Math::Point3D &position, double intensity, Math::Vector3D color = Math::Vector3D(1, 1, 1));
            Math::Vector3D illuminate(const Math::Point3D &point, const Math::Vector3D &normal) const override;
            Math::Vector3D shadowDir(const Math::Point3D &point) const override;
            double shadowMaxDistance(const Math::Point3D &point) const override;

        private:
            Math::Point3D _position;
    };
}
