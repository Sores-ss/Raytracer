/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-7
** File description:
** LightFactory
*/

#pragma once

#include <memory>

#include <libconfig.h++>

#include "lights/ILight.hpp"

namespace RayTracer
{
    class LightFactory
    {
        public:
            static std::unique_ptr<ILight> createAmbient(double intensity);
            static std::unique_ptr<ILight> createAmbient(const libconfig::Setting &cfg);
            static std::unique_ptr<ILight> createDirectional(const libconfig::Setting &cfg);
            static std::unique_ptr<ILight> createPoint(const libconfig::Setting &cfg);
    };
}
