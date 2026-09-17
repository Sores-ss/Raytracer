/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-7
** File description:
** Triangle - Ray-Triangle intersection using Möller–Trumbore algorithm
*/

#pragma once

#include "primitives/APrimitive.hpp"

namespace RayTracer
{
    class Triangle : public APrimitive
    {
        public:
            Triangle(const Math::Point3D &v0, const Math::Point3D &v1, const Math::Point3D &v2,
                     const Math::Vector3D &color);

            bool hits(const Ray &ray, double &t) const override;
            Math::Vector3D getNormalAt(const Math::Point3D &point) const override;
            void translate(const Math::Vector3D &offset) override;

        private:
            Math::Point3D _v1;
            Math::Point3D _v2;
            Math::Vector3D _normal;

            Math::Vector3D computeNormal() const;
    };
}
