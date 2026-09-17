#include "lights/ALight.hpp"

#include <limits>

namespace RayTracer {

ALight::ALight(double intensity, Math::Vector3D color)
    : _intensity(intensity), _color(color) {}

Math::Vector3D ALight::shadowDir(const Math::Point3D &) const {
    return Math::Vector3D(0, 0, 0);
}

double ALight::shadowMaxDistance(const Math::Point3D &) const {
    return std::numeric_limits<double>::infinity();
}

}
