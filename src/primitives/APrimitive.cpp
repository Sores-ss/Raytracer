/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-7
** File description:
** APrimitive
*/

#include "primitives/APrimitive.hpp"

#include <algorithm>
#include <cmath>

namespace RayTracer
{
    static const double APDEG = 3.14159265358979323846 / 180.0;

    APrimitive::APrimitive(const Math::Point3D &origin, const Math::Vector3D &color) : _origin(origin), _color(color), _specularStrength(0.35), _shininess(48.0), _reflectivity(0.0), _hasCheckerboard(false), _checkerColor(0, 0, 0), _checkerCellSize(1.0)
    {
    }

    Math::Vector3D APrimitive::getColor() const
    {
        return _color;
    }

    Math::Vector3D APrimitive::getColorAt(const Math::Point3D &point) const
    {
        if (!_hasCheckerboard)
            return _color;
        int cx = static_cast<int>(std::floor(point.x / _checkerCellSize));
        int cz = static_cast<int>(std::floor(point.z / _checkerCellSize));

        if (((cx + cz) & 1) == 0)
            return _color;
        return _checkerColor;
    }

    double APrimitive::getSpecularStrength() const
    {
        return _specularStrength;
    }

    double APrimitive::getShininess() const
    {
        return _shininess;
    }

    double APrimitive::getReflectivity() const
    {
        return _reflectivity;
    }

    void APrimitive::setSpecularStrength(double specular)
    {
        _specularStrength = std::max(0.0, specular);
    }

    void APrimitive::setShininess(double shininess)
    {
        _shininess = std::max(1.0, shininess);
    }

    void APrimitive::setReflectivity(double reflectivity)
    {
        _reflectivity = std::clamp(reflectivity, 0.0, 1.0);
    }

    void APrimitive::setCheckerboard(const Math::Vector3D &secondColor, double cellSize)
    {
        _checkerColor = secondColor;
        _checkerCellSize = std::max(0.01, cellSize);
        _hasCheckerboard = true;
    }

    void APrimitive::setCheckerboardEnabled(bool enabled)
    {
        _hasCheckerboard = enabled;
    }

    void APrimitive::translate(const Math::Vector3D &offset)
    {
        _origin = _origin + offset;
    }

    void APrimitive::scale(const Math::Vector3D &factors)
    {
        _origin = Math::Point3D(_origin.x * factors.x, _origin.y * factors.y, _origin.z * factors.z);
    }

    void APrimitive::rotateX(double deg)
    {
        double rad;
        double c;
        double s;
        double ny;
        double nz;
        
        rad = deg * APDEG;
        c = std::cos(rad);
        s = std::sin(rad);
        ny = _origin.y * c - _origin.z * s;
        nz = _origin.y * s + _origin.z * c;
        _origin = Math::Point3D(_origin.x, ny, nz);
    }

    void APrimitive::rotateY(double deg)
    {
        double rad;
        double c;
        double s;
        double nx;
        double nz;

        rad = deg * APDEG;
        c = std::cos(rad);
        s = std::sin(rad);
        nx = _origin.x * c + _origin.z * s;
        nz = -_origin.x * s + _origin.z * c;
        _origin = Math::Point3D(nx, _origin.y, nz);
    }

    void APrimitive::rotateZ(double deg)
    {
        double rad;
        double c;
        double s;
        double nx;
        double ny;

        rad = deg * APDEG;
        c = std::cos(rad);
        s = std::sin(rad);
        nx = _origin.x * c - _origin.y * s;
        ny = _origin.x * s + _origin.y * c;
        _origin = Math::Point3D(nx, ny, _origin.z);
    }
}
