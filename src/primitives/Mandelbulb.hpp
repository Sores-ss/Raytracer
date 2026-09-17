/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-7
** File description:
** Mandelbulb - 3D fractal with SDF
*/

#pragma once

#include "primitives/APrimitive.hpp"
#include "primitives/ISdf.hpp"

namespace RayTracer
{
    class Mandelbulb : public APrimitive, public ISdf
    {
        public:
            Mandelbulb(const Math::Point3D &center, double scale, int iterations,
                       const Math::Vector3D &color);

            bool hits(const Ray &ray, double &t) const override;
            Math::Vector3D getNormalAt(const Math::Point3D &point) const override;

            double distance(const Math::Point3D &point) const override;

        private:
            double _scale;
            int _iterations;
            static constexpr double MARCH_MAX_STEPS = 128;
            static constexpr double MARCH_MAX_DIST = 100.0;
            static constexpr double MARCH_EPSILON = 1e-5;
            static constexpr double POWER = 8.0;
    };
}
