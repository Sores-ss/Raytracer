#include "lights/PointLight.hpp"

#include <algorithm>

namespace RayTracer {

PointLight::PointLight(const Math::Point3D &position, double intensity, Math::Vector3D color)
    : ALight(intensity, color), _position(position) {}

Math::Vector3D PointLight::illuminate(const Math::Point3D &point, const Math::Vector3D &normal) const {
    Math::Vector3D dir = (_position - point).normalize();
    double factor = std::max(0.0, normal.dot(dir));
    return _color * _intensity * factor;
}

Math::Vector3D PointLight::shadowDir(const Math::Point3D &point) const {
    return (_position - point).normalize();
}

double PointLight::shadowMaxDistance(const Math::Point3D &point) const {
    return (_position - point).length();
}

}
