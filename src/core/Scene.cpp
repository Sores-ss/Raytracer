#include "core/Scene.hpp"

namespace RayTracer {

void Scene::addPrimitive(std::unique_ptr<IPrimitive> p) {
    _primitives.push_back(std::move(p));
}

void Scene::addLight(std::unique_ptr<ILight> l) {
    _lights.push_back(std::move(l));
}

const Camera &Scene::getCamera() const {
    return _camera;
}

void Scene::setCamera(const Camera &cam) {
    _camera = cam;
}

const std::vector<std::unique_ptr<IPrimitive>> &Scene::getPrimitives() const {
    return _primitives;
}

const std::vector<std::unique_ptr<ILight>> &Scene::getLights() const {
    return _lights;
}

void Scene::setResolution(int width, int height) {
    _width = width;
    _height = height;
}

int Scene::getWidth() const { return _width; }
int Scene::getHeight() const { return _height; }

bool Scene::hits(const Ray &ray, double &t, IPrimitive *&hit) const {
    double closest = 1e9;
    hit = nullptr;
    for (const auto &p : _primitives) {
        double tCand;
        if (p->hits(ray, tCand) && tCand < closest) {
            closest = tCand;
            hit = p.get();
        }
    }
    if (hit) {
        t = closest;
        return true;
    }
    return false;
}

}
