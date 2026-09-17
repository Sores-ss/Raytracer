#include "lights/DirectionalLight.hpp"

#include <algorithm>

namespace RayTracer {

DirectionalLight::DirectionalLight(const Math::Vector3D &direction, double intensity,
                                   Math::Vector3D color)
    : ALight(intensity, color), _direction(direction.normalize()) {}

Math::Vector3D DirectionalLight::illuminate(const Math::Point3D &, const Math::Vector3D &normal) const {
    double factor = std::max(0.0, normal.dot(_direction));
    return _color * _intensity * factor;
}

Math::Vector3D DirectionalLight::shadowDir(const Math::Point3D &) const {
    return _direction;
}

}
