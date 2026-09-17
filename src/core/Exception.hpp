/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-7
** File description:
** Exception
*/

#pragma once

#include <stdexcept>
#include <string>

namespace RayTracer
{

    class Exception : public std::runtime_error
    {
        public:
            explicit Exception(const std::string &msg) : std::runtime_error(msg) {}
    };
}
