#pragma once

#include "core/Scene.hpp"
#include "output/IRenderOutput.hpp"

namespace RayTracer {

class Renderer {
public:
    void render(const Scene &scene, int width, int height, IRenderOutput &out) const;
};

}
