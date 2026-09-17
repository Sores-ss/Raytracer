#pragma once

#include <string>

#include "core/Scene.hpp"

namespace RayTracer {

class SceneParser {
public:
    SceneParser(const std::string &path);
    Scene parse();

private:
    std::string _path;
};

}
