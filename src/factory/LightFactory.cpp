#include "factory/LightFactory.hpp"

#include "lights/AmbientLight.hpp"
#include "lights/DirectionalLight.hpp"

namespace RayTracer {

static double asDouble(const libconfig::Setting &s) {
    if (s.getType() == libconfig::Setting::TypeInt)
        return static_cast<int>(s);
    return static_cast<double>(s);
}

std::unique_ptr<ILight> LightFactory::createAmbient(double intensity) {
    return std::make_unique<AmbientLight>(intensity);
}

std::unique_ptr<ILight> LightFactory::createDirectional(const libconfig::Setting &cfg) {
    double x = asDouble(cfg["x"]);
    double y = asDouble(cfg["y"]);
    double z = asDouble(cfg["z"]);
    double intensity = asDouble(cfg["intensity"]);
    return std::make_unique<DirectionalLight>(Math::Vector3D(x, y, z), intensity);
}

}
