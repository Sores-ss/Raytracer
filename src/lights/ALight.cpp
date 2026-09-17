#include "lights/ALight.hpp"

#include "math/Vector3D.hpp"

namespace RayTracer {

ALight::ALight(double intensity) : _intensity(intensity) {}

Math::Vector3D ALight::shadowDir() const {
    return Math::Vector3D(0, 0, 0);
}

}
