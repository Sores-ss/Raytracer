#include "core/Ray.hpp"

namespace RayTracer {

Ray::Ray(const Math::Point3D &origin, const Math::Vector3D &direction)
    : origin(origin), direction(direction) {}

}
