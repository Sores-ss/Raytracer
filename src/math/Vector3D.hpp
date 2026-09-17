/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-7
** File description:
** Vector3D
*/

#pragma once

namespace Math
{
    class Vector3D
    {
        public:
            double x;
            double y;
            double z;

            Vector3D();
            Vector3D(double x, double y, double z);
            double length() const;
            double dot(const Vector3D &v) const;
            Vector3D normalize() const;
            Vector3D operator+(const Vector3D &v) const;
            Vector3D operator-(const Vector3D &v) const;
            Vector3D operator*(const Vector3D &v) const;
            Vector3D operator/(const Vector3D &v) const;
            Vector3D operator*(double t) const;
            Vector3D operator/(double t) const;
            Vector3D &operator+=(const Vector3D &v);
            Vector3D &operator-=(const Vector3D &v);
            Vector3D &operator*=(const Vector3D &v);
            Vector3D &operator/=(const Vector3D &v);
            Vector3D &operator*=(double t);
            Vector3D &operator/=(double t);
    };
}
