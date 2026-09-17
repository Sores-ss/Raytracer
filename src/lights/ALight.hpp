#pragma once

#include "lights/ILight.hpp"
#include "math/Vector3D.hpp"

namespace RayTracer {

class ALight : public ILight {
public:
    ALight(double intensity, Math::Vector3D color = Math::Vector3D(1, 1, 1));
    ~ALight() override = default;

    Math::Vector3D shadowDir(const Math::Point3D &point) const override;
    double shadowMaxDistance(const Math::Point3D &point) const override;

protected:
    double _intensity;
    Math::Vector3D _color;
};

}
