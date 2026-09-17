#include "lights/AmbientLight.hpp"

namespace RayTracer {

AmbientLight::AmbientLight(double intensity) : ALight(intensity) {}

Math::Vector3D AmbientLight::illuminate(const Math::Point3D &, const Math::Vector3D &) const {
    return Math::Vector3D(_intensity, _intensity, _intensity);
}

}
