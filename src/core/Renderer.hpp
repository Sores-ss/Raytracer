#pragma once

#include "core/Scene.hpp"

namespace RayTracer {

class Renderer {
public:
    void render(const Scene &scene, int width, int height) const;
};

}
