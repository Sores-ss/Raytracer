#pragma once

#include "lights/ALight.hpp"

namespace RayTracer {

class AmbientLight : public ALight {
public:
    AmbientLight(double intensity);

    Math::Vector3D illuminate(const Math::Point3D &point, const Math::Vector3D &normal) const override;
};

}
