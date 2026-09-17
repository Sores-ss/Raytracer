/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-7
** File description:
** SceneParser
*/

#pragma once

#include <string>

#include "core/Scene.hpp"

namespace RayTracer
{
    class SceneParser
    {
        public:
            SceneParser(const std::string &path);
            Scene parse();

        private:
            std::string _path;
    };
}
