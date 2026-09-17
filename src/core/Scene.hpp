#pragma once

#include <memory>
#include <vector>

#include "core/Camera.hpp"
#include "lights/ILight.hpp"
#include "primitives/IPrimitive.hpp"

namespace RayTracer {

class Scene {
public:
    Scene() = default;

    void addPrimitive(std::unique_ptr<IPrimitive> p);
    void addLight(std::unique_ptr<ILight> l);

    const Camera &getCamera() const;
    void setCamera(const Camera &cam);

    const std::vector<std::unique_ptr<IPrimitive>> &getPrimitives() const;
    const std::vector<std::unique_ptr<ILight>> &getLights() const;

    void setResolution(int width, int height);
    int getWidth() const;
    int getHeight() const;

    bool hits(const Ray &ray, double &t, IPrimitive *&hit) const;

private:
    Camera _camera;
    std::vector<std::unique_ptr<IPrimitive>> _primitives;
    std::vector<std::unique_ptr<ILight>> _lights;
    int _width = 400;
    int _height = 400;
};

}
