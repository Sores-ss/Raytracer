#pragma once

#include "lights/ILight.hpp"

namespace RayTracer {

class ALight : public ILight {
public:
    ALight(double intensity);
    ~ALight() override = default;

    Math::Vector3D shadowDir() const override;

protected:
    double _intensity;
};

}
