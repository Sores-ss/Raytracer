#include "primitives/APrimitive.hpp"

namespace RayTracer {

APrimitive::APrimitive(const Math::Point3D &origin, const Math::Vector3D &color)
    : _origin(origin), _color(color) {}

Math::Vector3D APrimitive::getColor() const {
    return _color;
}

void APrimitive::translate(const Math::Vector3D &offset) {
    _origin = _origin + offset;
}

}
