#pragma once

#include "math/Vector3D.hpp"

namespace RayTracer {

class IRenderOutput {
public:
    virtual ~IRenderOutput() = default;
    virtual void begin(int width, int height) = 0;
    virtual void writePixel(int x, int y, const Math::Vector3D &color) = 0;
    virtual void endRow(int y) = 0;
    virtual void finish() = 0;
};

}
