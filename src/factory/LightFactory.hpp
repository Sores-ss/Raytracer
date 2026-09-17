#pragma once

#include <memory>

#include <libconfig.h++>

#include "lights/ILight.hpp"

namespace RayTracer {

class LightFactory {
public:
    static std::unique_ptr<ILight> createAmbient(double intensity);
    static std::unique_ptr<ILight> createDirectional(const libconfig::Setting &cfg);
};

}
