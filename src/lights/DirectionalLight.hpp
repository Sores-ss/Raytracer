#pragma once

#include "lights/ALight.hpp"

namespace RayTracer {

class DirectionalLight : public ALight {
public:
    DirectionalLight(const Math::Vector3D &direction, double intensity);

    Math::Vector3D illuminate(const Math::Point3D &point, const Math::Vector3D &normal) const override;
    Math::Vector3D shadowDir() const override;

private:
    Math::Vector3D _direction;
};

}
