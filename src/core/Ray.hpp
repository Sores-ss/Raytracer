#pragma once

#include "math/Point3D.hpp"
#include "math/Vector3D.hpp"

namespace RayTracer {

class Ray {
public:
    Math::Point3D origin;
    Math::Vector3D direction;

    Ray() = default;
    Ray(const Math::Point3D &origin, const Math::Vector3D &direction);
};

}
