#pragma once

#include <memory>
#include <string>

#include <libconfig.h++>

#include "primitives/IPrimitive.hpp"

namespace RayTracer {

class PrimitiveFactory {
public:
    static std::unique_ptr<IPrimitive> create(const std::string &type, const libconfig::Setting &cfg);
};

}
