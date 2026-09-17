#pragma once

#include "math/Point3D.hpp"
#include "math/Vector3D.hpp"

namespace RayTracer {

class ILight {
public:
    virtual ~ILight() = default;
    virtual Math::Vector3D illuminate(const Math::Point3D &point, const Math::Vector3D &normal) const = 0;
};

}
