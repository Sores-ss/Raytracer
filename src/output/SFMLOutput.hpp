/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-7
** File description:
** SFMLOutput
*/

#pragma once

#include <SFML/Graphics.hpp>

#include "output/IRenderOutput.hpp"

namespace RayTracer
{
    class SFMLOutput : public IRenderOutput
    {
        public:
            void begin(int width, int height) override;
            void writePixel(int x, int y, const Math::Vector3D &color) override;
            void endRow(int y) override;
            void finish() override;

        private:
            sf::RenderWindow _window;
            sf::Image _image;
            sf::Texture _texture;
            sf::Sprite _sprite;
    };
}
