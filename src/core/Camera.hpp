/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-7
** File description:
** Camera
*/

#pragma once

#include "math/Point3D.hpp"
#include "math/Rectangle3D.hpp"
#include "core/Ray.hpp"

namespace RayTracer
{
    class Camera
    {
        public:
            Math::Point3D origin;
            Math::Rectangle3D screen;

            Camera();
            Camera(const Camera &other) = default;
            Camera &operator=(const Camera &other) = default;
            ~Camera() = default;
            Ray ray(double u, double v) const;
    };

}
