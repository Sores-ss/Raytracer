/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-7
** File description:
** APrimitive
*/

#pragma once

#include "primitives/IPrimitive.hpp"

namespace RayTracer
{
    class APrimitive : public IPrimitive
    {
        public:
            APrimitive(const Math::Point3D &origin, const Math::Vector3D &color);
            ~APrimitive() override = default;

            Math::Vector3D getColor() const override;
            double getSpecularStrength() const override;
            double getShininess() const override;
            void setSpecularStrength(double specular) override;
            void setShininess(double shininess) override;
            void translate(const Math::Vector3D &offset) override;
            void rotateX(double deg) override;
            void rotateY(double deg) override;
            void rotateZ(double deg) override;

        protected:
            Math::Point3D _origin;
            Math::Vector3D _color;
            double _specularStrength;
            double _shininess;
    };
}
