/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-7
** File description:
** Point3D
*/

#pragma once

#include "Vector3D.hpp"

namespace Math
{
    class Point3D
    {
        public:
            double x;
            double y;
            double z;
            Point3D();
            Point3D(double x, double y, double z);
            Point3D operator+(const Vector3D &v) const;
            Vector3D operator-(const Point3D &other) const;
    };
}
