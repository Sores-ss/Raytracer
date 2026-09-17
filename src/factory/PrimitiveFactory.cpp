/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-7
** File description:
** PrimitiveFactory
*/

#include "factory/PrimitiveFactory.hpp"

#include "core/Exception.hpp"
#include "primitives/Cone.hpp"
#include "primitives/Cylinder.hpp"
#include "primitives/Plane.hpp"
#include "primitives/Sphere.hpp"

namespace RayTracer
{
    static double asDouble(const libconfig::Setting &s)
    {
        if (s.getType() == libconfig::Setting::TypeInt)
            return static_cast<int>(s);
        return static_cast<double>(s);
    }

    static Math::Vector3D readColor(const libconfig::Setting &cfg)
    {
        double r;
        double g;
        double b;

        r = asDouble(cfg["r"]) / 255.0;
        g = asDouble(cfg["g"]) / 255.0;
        b = asDouble(cfg["b"]) / 255.0;
        return Math::Vector3D(r, g, b);
    }

    static void applyMaterial(IPrimitive &primitive, const libconfig::Setting &cfg)
    {
        if (cfg.exists("specular"))
            primitive.setSpecularStrength(asDouble(cfg["specular"]));
        if (cfg.exists("shininess"))
            primitive.setShininess(asDouble(cfg["shininess"]));
        if (cfg.exists("reflectivity"))
            primitive.setReflectivity(asDouble(cfg["reflectivity"]));
    }

    std::unique_ptr<IPrimitive> PrimitiveFactory::create(const std::string &type, const libconfig::Setting &cfg)
    {
        if (type == "sphere") {
            double x = asDouble(cfg["x"]);
            double y = asDouble(cfg["y"]);
            double z = asDouble(cfg["z"]);
            double r = asDouble(cfg["r"]);
            Math::Vector3D color = readColor(cfg["color"]);
            auto primitive = std::make_unique<Sphere>(Math::Point3D(x, y, z), r, color);
            applyMaterial(*primitive, cfg);
            return primitive;
        }

        if (type == "plane") {
            std::string axis = (const char *)cfg["axis"];
            double pos = asDouble(cfg["position"]);
            Math::Vector3D normal(0, 0, 0);
            Math::Point3D origin(0, 0, 0);
            if (axis == "X"){
                normal = Math::Vector3D(1, 0, 0);
                origin = Math::Point3D(pos, 0, 0);
            }
            else if (axis == "Y") {
                normal = Math::Vector3D(0, 1, 0);
                origin = Math::Point3D(0, pos, 0);
            }
            else if (axis == "Z") {
                normal = Math::Vector3D(0, 0, 1);
                origin = Math::Point3D(0, 0, pos);
            }
            else throw 
                Exception("unknown plane axis: " + axis);
            Math::Vector3D color = readColor(cfg["color"]);
            auto primitive = std::make_unique<Plane>(origin, normal, color);
            applyMaterial(*primitive, cfg);
            return primitive;
        }

        if (type == "cylinder") {
            double x = asDouble(cfg["x"]);
            double y = asDouble(cfg["y"]);
            double z = asDouble(cfg["z"]);
            double r = asDouble(cfg["r"]);
            Math::Vector3D axis(asDouble(cfg["axis"]["x"]), asDouble(cfg["axis"]["y"]), asDouble(cfg["axis"]["z"]));
            Math::Vector3D color = readColor(cfg["color"]);
            auto primitive = std::make_unique<Cylinder>(Math::Point3D(x, y, z), r, axis, color);
            applyMaterial(*primitive, cfg);
            return primitive;
        }

        if (type == "cone") {
            double x = asDouble(cfg["x"]);
            double y = asDouble(cfg["y"]);
            double z = asDouble(cfg["z"]);
            double angle = asDouble(cfg["angle"]);
            Math::Vector3D axis(asDouble(cfg["axis"]["x"]), asDouble(cfg["axis"]["y"]), asDouble(cfg["axis"]["z"]));
            Math::Vector3D color = readColor(cfg["color"]);
            auto primitive = std::make_unique<Cone>(Math::Point3D(x, y, z), angle, axis, color);
            applyMaterial(*primitive, cfg);
            return primitive;
        }
        throw Exception("unknown primitive type: " + type);
    }
}
