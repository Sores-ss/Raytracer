/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-7
** File description:
** Rectangle3D
*/

#include "Rectangle3D.hpp"

namespace Math
{
    Rectangle3D::Rectangle3D(const Point3D &origin, const Vector3D &bottom_side, const Vector3D &left_side) : origin(origin), bottom_side(bottom_side), left_side(left_side) {}

    Point3D Rectangle3D::pointAt(double u, double v) const
    {
        return origin + bottom_side * u + left_side * v;
    }
}
