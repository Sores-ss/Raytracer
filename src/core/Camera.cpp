#include "core/Camera.hpp"

namespace RayTracer {

Camera::Camera()
    : origin(Math::Point3D(0, 0, 0)),
      screen(Math::Rectangle3D(
          Math::Point3D(-1, -1, -1),
          Math::Vector3D(2, 0, 0),
          Math::Vector3D(0, 2, 0))) {}

Ray Camera::ray(double u, double v) const {
    Math::Point3D target = screen.pointAt(u, v);
    return Ray(origin, target - origin);
}

}
