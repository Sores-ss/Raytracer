#pragma once

#include "primitives/APrimitive.hpp"

namespace RayTracer {

class Sphere : public APrimitive {
public:
    Sphere(const Math::Point3D &center, double radius, const Math::Vector3D &color);

    bool hits(const Ray &ray, double &t) const override;
    Math::Vector3D getNormalAt(const Math::Point3D &point) const override;

private:
    double _radius;
};

}
