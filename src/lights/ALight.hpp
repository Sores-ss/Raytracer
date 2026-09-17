#pragma once

#include "lights/ILight.hpp"

namespace RayTracer {

class ALight : public ILight {
public:
    ALight(double intensity);
    ~ALight() override = default;

protected:
    double _intensity;
};

}
