#pragma once

#include "primitives/APrimitive.hpp"

namespace RayTracer {

class Cylinder : public APrimitive {
public:
    Cylinder(const Math::Point3D &origin, double radius, const Math::Vector3D &axis, const Math::Vector3D &color);

    bool hits(const Ray &ray, double &t) const override;
    Math::Vector3D getNormalAt(const Math::Point3D &point) const override;
    void rotateX(double deg) override;
    void rotateY(double deg) override;
    void rotateZ(double deg) override;

private:
    double _radius;
    Math::Vector3D _axis;
};

}
