#pragma once

#include <ostream>

#include "output/IRenderOutput.hpp"

namespace RayTracer {

class PPMOutput : public IRenderOutput {
public:
    PPMOutput(std::ostream &out);

    void begin(int width, int height) override;
    void writePixel(int x, int y, const Math::Vector3D &color) override;
    void endRow(int y) override;
    void finish() override;

private:
    std::ostream &_out;
};

}
