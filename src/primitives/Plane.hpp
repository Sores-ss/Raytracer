/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-7
** File description:
** Plane
*/

#pragma once

#include "primitives/APrimitive.hpp"

namespace RayTracer
{
    class Plane : public APrimitive
    {
        public:
            Plane(const Math::Point3D &origin, const Math::Vector3D &normal, const Math::Vector3D &color);
            bool hits(const Ray &ray, double &t) const override;
            Math::Vector3D getNormalAt(const Math::Point3D &point) const override;
            Math::Vector3D getColorAt(const Math::Point3D &point) const override;

        private:
            Math::Vector3D _normal;
    };
}
