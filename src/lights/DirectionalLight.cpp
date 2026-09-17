#include "lights/DirectionalLight.hpp"

#include <algorithm>

namespace RayTracer {

DirectionalLight::DirectionalLight(const Math::Vector3D &direction, double intensity)
    : ALight(intensity), _direction(direction.normalize()) {}

Math::Vector3D DirectionalLight::illuminate(const Math::Point3D &, const Math::Vector3D &normal) const {
    double d = std::max(0.0, normal.dot(_direction)) * _intensity;
    return Math::Vector3D(d, d, d);
}

}
