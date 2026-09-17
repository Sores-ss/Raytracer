/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-7
** File description:
** Renderer
*/

#pragma once

#include "core/Scene.hpp"
#include "output/IRenderOutput.hpp"

namespace RayTracer
{
    class Renderer
    {
        public:
            void render(const Scene &scene, int width, int height, IRenderOutput &out) const;
    };

}
