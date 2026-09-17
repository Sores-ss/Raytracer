#pragma once

#include "primitives/APrimitive.hpp"

namespace RayTracer {

class Cone : public APrimitive {
public:
    Cone(const Math::Point3D &apex, double angleDeg, const Math::Vector3D &axis, const Math::Vector3D &color);

    bool hits(const Ray &ray, double &t) const override;
    Math::Vector3D getNormalAt(const Math::Point3D &point) const override;
    void rotateX(double deg) override;
    void rotateY(double deg) override;
    void rotateZ(double deg) override;

private:
    double _angle;
    Math::Vector3D _axis;
};

}
