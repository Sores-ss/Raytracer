/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-7
** File description:
** SFMLOutput
*/

#include "output/SFMLOutput.hpp"

#include <algorithm>

namespace RayTracer
{
    void SFMLOutput::begin(int width, int height)
    {
        _window.create(sf::VideoMode(width, height), "Raytracer", sf::Style::Close);
        _window.setFramerateLimit(60);
        _image.create(width, height, sf::Color::Black);
        _texture.create(width, height);
        _sprite.setTexture(_texture);
    }

    void SFMLOutput::writePixel(int x, int y, const Math::Vector3D &color)
    {
        if (!_window.isOpen())
            return;
        sf::Uint8 r = static_cast<sf::Uint8>(std::clamp(color.x, 0.0, 1.0) * 255);
        sf::Uint8 g = static_cast<sf::Uint8>(std::clamp(color.y, 0.0, 1.0) * 255);
        sf::Uint8 b = static_cast<sf::Uint8>(std::clamp(color.z, 0.0, 1.0) * 255);
        _image.setPixel(x, y, sf::Color(r, g, b));
    }

    void SFMLOutput::endRow(int)
    {
        if (!_window.isOpen())
            return;
        sf::Event event;
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                _window.close();
        }
        if (!_window.isOpen())
            return;
        _texture.update(_image);
        _window.clear();
        _window.draw(_sprite);
        _window.display();
    }

    void SFMLOutput::finish()
    {
        while (_window.isOpen()) {
            sf::Event event;
            while (_window.pollEvent(event)) {
                if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                    _window.close();
            }
            _window.clear();
            _window.draw(_sprite);
            _window.display();
        }
    }
}
