#include "factory/LightFactory.hpp"

#include "lights/AmbientLight.hpp"
#include "lights/DirectionalLight.hpp"
#include "lights/PointLight.hpp"
#include "math/Point3D.hpp"

namespace RayTracer {

static double asDouble(const libconfig::Setting &s) {
    if (s.getType() == libconfig::Setting::TypeInt)
        return static_cast<int>(s);
    return static_cast<double>(s);
}

static Math::Vector3D readColorOrWhite(const libconfig::Setting &cfg) {
    if (!cfg.exists("color"))
        return Math::Vector3D(1, 1, 1);
    const libconfig::Setting &c = cfg["color"];
    return Math::Vector3D(asDouble(c["r"]) / 255.0,
                          asDouble(c["g"]) / 255.0,
                          asDouble(c["b"]) / 255.0);
}

std::unique_ptr<ILight> LightFactory::createAmbient(double intensity) {
    return std::make_unique<AmbientLight>(intensity);
}

std::unique_ptr<ILight> LightFactory::createAmbient(const libconfig::Setting &cfg) {
    double intensity = asDouble(cfg["intensity"]);
    return std::make_unique<AmbientLight>(intensity, readColorOrWhite(cfg));
}

std::unique_ptr<ILight> LightFactory::createDirectional(const libconfig::Setting &cfg) {
    double x = asDouble(cfg["x"]);
    double y = asDouble(cfg["y"]);
    double z = asDouble(cfg["z"]);
    double intensity = asDouble(cfg["intensity"]);
    return std::make_unique<DirectionalLight>(Math::Vector3D(x, y, z), intensity, readColorOrWhite(cfg));
}

std::unique_ptr<ILight> LightFactory::createPoint(const libconfig::Setting &cfg) {
    double x = asDouble(cfg["x"]);
    double y = asDouble(cfg["y"]);
    double z = asDouble(cfg["z"]);
    double intensity = asDouble(cfg["intensity"]);
    return std::make_unique<PointLight>(Math::Point3D(x, y, z), intensity, readColorOrWhite(cfg));
}

}
