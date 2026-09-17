/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-7
** File description:
** IPrimitive
*/

#pragma once

#include "core/Ray.hpp"
#include "math/Point3D.hpp"
#include "math/Vector3D.hpp"

namespace RayTracer
{
    class IPrimitive
    {
        public:
            virtual ~IPrimitive() = default;
            virtual bool hits(const Ray &ray, double &t) const = 0;
            virtual Math::Vector3D getNormalAt(const Math::Point3D &point) const = 0;
            virtual Math::Vector3D getColor() const = 0;
            virtual Math::Vector3D getColorAt(const Math::Point3D &point) const = 0;
            virtual double getSpecularStrength() const = 0;
            virtual double getShininess() const = 0;
            virtual double getReflectivity() const = 0;
            virtual void setSpecularStrength(double specular) = 0;
            virtual void setShininess(double shininess) = 0;
            virtual void setReflectivity(double reflectivity) = 0;
            virtual void setCheckerboard(const Math::Vector3D &secondColor, double cellSize) = 0;
            virtual void setCheckerboardEnabled(bool enabled) = 0;
            virtual void translate(const Math::Vector3D &offset) = 0;
            virtual void scale(const Math::Vector3D &factors) = 0;
            virtual void rotateX(double deg) = 0;
            virtual void rotateY(double deg) = 0;
            virtual void rotateZ(double deg) = 0;
    };
}
