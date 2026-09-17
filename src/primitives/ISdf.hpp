/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-7
** File description:
** ISdf - Signed Distance Function interface for fractals
*/

#pragma once

#include "math/Point3D.hpp"
#include "math/Vector3D.hpp"

namespace RayTracer
{
    class ISdf
    {
        public:
            virtual ~ISdf() = default;
            
            virtual double distance(const Math::Point3D &point) const = 0;
            
            virtual Math::Vector3D normal(const Math::Point3D &point) const;
    };
}
