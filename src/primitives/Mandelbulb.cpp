/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-7
** File description:
** Mandelbulb - Sphere tracing for 3D Mandelbrot set
*/

#include "primitives/Mandelbulb.hpp"

#include <cmath>
#include <algorithm>

namespace RayTracer
{
    Mandelbulb::Mandelbulb(const Math::Point3D &center, double scale, int iterations,
                           const Math::Vector3D &color)
        : APrimitive(center, color), _scale(scale), _iterations(iterations)
    {
    }

    double Mandelbulb::distance(const Math::Point3D &point) const
    {
        Math::Vector3D p = point - _origin;
        Math::Vector3D z = p;
        double r = 0.0;
        double dr = 1.0;

        for (int i = 0; i < _iterations; ++i)
        {
            r = z.length();
            
            if (r > 2.0)
                break;
            
            double theta = std::atan2(z.x, z.z);
            double phi = std::acos(std::max(-1.0, std::min(1.0, z.y / r)));
            
            double rn = std::pow(r, POWER);
            double ntheta = POWER * theta;
            double nphi = POWER * phi;
            
            double sin_nphi = std::sin(nphi);
            z = Math::Vector3D(
                rn * sin_nphi * std::sin(ntheta),
                rn * std::cos(nphi),
                rn * sin_nphi * std::cos(ntheta)
            );
            
            z = z + p;
            
            dr = dr * POWER * std::pow(r, POWER - 1.0) + 1.0;
        }

        return 0.5 * r * std::log(r) / dr;
    }

    bool Mandelbulb::hits(const Ray &ray, double &t) const
    {
        double totalDist = 0.0;
        Math::Point3D currentPoint = ray.origin;

        for (int step = 0; step < MARCH_MAX_STEPS; ++step)
        {
            double dist = distance(currentPoint);

            if (dist < MARCH_EPSILON)
            {
                t = totalDist;
                return true;
            }

            if (totalDist > MARCH_MAX_DIST)
                return false;

            currentPoint = currentPoint + ray.direction * dist;
            totalDist += dist;
        }

        return false;
    }

    Math::Vector3D Mandelbulb::getNormalAt(const Math::Point3D &point) const
    {
        constexpr double h = 1e-5;
        
        double d0 = distance(point);
        double dx = distance(point + Math::Vector3D(h, 0, 0)) - d0;
        double dy = distance(point + Math::Vector3D(0, h, 0)) - d0;
        double dz = distance(point + Math::Vector3D(0, 0, h)) - d0;

        Math::Vector3D grad(dx / h, dy / h, dz / h);
        double len = grad.length();
        
        if (len < 1e-10)
            return Math::Vector3D(0, 1, 0);

        return grad / len;
    }
}
