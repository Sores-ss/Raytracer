#pragma once

#include <SFML/Graphics.hpp>

#include "output/IRenderOutput.hpp"

namespace RayTracer {

class SFMLOutput : public IRenderOutput {
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
