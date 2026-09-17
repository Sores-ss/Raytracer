/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-7
** File description:
** PPMOutput
*/

#include "output/PPMOutput.hpp"

#include <algorithm>

namespace RayTracer
{

    PPMOutput::PPMOutput(std::ostream &out) : _out(out)
    {
    }

    void PPMOutput::begin(int width, int height)
    {
        _out << "P3\n" << width << " " << height << "\n255\n";
    }

    void PPMOutput::writePixel(int, int, const Math::Vector3D &color)
    {
        int r;
        int g;
        int b;

        r = static_cast<int>(std::clamp(color.x, 0.0, 1.0) * 255);
        g = static_cast<int>(std::clamp(color.y, 0.0, 1.0) * 255);
        b = static_cast<int>(std::clamp(color.z, 0.0, 1.0) * 255);
        _out << r << " " << g << " " << b << "\n";
    }

    void PPMOutput::endRow(int)
    {
    }

    void PPMOutput::finish() 
    {
    }
}
