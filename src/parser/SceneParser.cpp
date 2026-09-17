/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-7
** File description:
** SceneParser
*/

#include "parser/SceneParser.hpp"

#include <cmath>

#include <libconfig.h++>

#include "core/Exception.hpp"
#include "factory/LightFactory.hpp"
#include "factory/PrimitiveFactory.hpp"
#include "math/Rectangle3D.hpp"

namespace RayTracer
{

    static const double PI = 3.14159265358979323846;

    static double asDouble(const libconfig::Setting &s)
    {
        if (s.getType() == libconfig::Setting::TypeInt)
            return static_cast<int>(s);
        return static_cast<double>(s);
    }

    static void parseCamera(const libconfig::Config &cfg, Scene &scene)
    {
        int w;
        int h;
        double px;
        double py;
        double pz;
        double fov;
        double aspect;
        double halfH;
        double halfW;

        const libconfig::Setting &cam = cfg.lookup("camera");
        w = (int)cam["resolution"]["width"];
        h = (int)cam["resolution"]["height"];
        scene.setResolution(w, h);
        px = asDouble(cam["position"]["x"]);
        py = asDouble(cam["position"]["y"]);
        pz = asDouble(cam["position"]["z"]);
        fov = asDouble(cam["fieldOfView"]);
        aspect = static_cast<double>(w) / h;
        halfH = std::tan(fov / 2.0 * PI / 180.0);
        halfW = aspect * halfH;
        Camera c;
        c.origin = Math::Point3D(px, py, pz);
        c.screen = Math::Rectangle3D(Math::Point3D(px - halfW, py - halfH, pz - 1.0), Math::Vector3D(2.0 * halfW, 0, 0), Math::Vector3D(0, 2.0 * halfH, 0));
        scene.setCamera(c);
    }

    static void applyTranslation(IPrimitive &prim, const libconfig::Setting &cfg)
    {
        if (!cfg.exists("translation"))
            return;
        const libconfig::Setting &t = cfg["translation"];
        prim.translate(Math::Vector3D(asDouble(t["x"]), asDouble(t["y"]), asDouble(t["z"])));
    }

    static void applyRotation(IPrimitive &prim, const libconfig::Setting &cfg)
    {
        if (!cfg.exists("rotation"))
            return;
        const libconfig::Setting &r = cfg["rotation"];
        if (r.exists("x"))
            prim.rotateX(asDouble(r["x"]));
        if (r.exists("y"))
            prim.rotateY(asDouble(r["y"]));
        if (r.exists("z"))
            prim.rotateZ(asDouble(r["z"]));
    }

    static void applyScale(IPrimitive &prim, const libconfig::Setting &cfg)
    {
        if (!cfg.exists("scale"))
            return;
        const libconfig::Setting &s = cfg["scale"];

        if (s.getType() == libconfig::Setting::TypeGroup) {
            double sx = s.exists("x") ? asDouble(s["x"]) : 1.0;
            double sy = s.exists("y") ? asDouble(s["y"]) : 1.0;
            double sz = s.exists("z") ? asDouble(s["z"]) : 1.0;

            prim.scale(Math::Vector3D(sx, sy, sz));
        } else {
            double uniform = asDouble(s);

            prim.scale(Math::Vector3D(uniform, uniform, uniform));
        }
    }

    static void parsePrimitives(const libconfig::Config &cfg, Scene &scene)
    {
        if (!cfg.exists("primitives"))
            return;
        const libconfig::Setting &prims = cfg.lookup("primitives");
        if (prims.exists("spheres")) {
            const libconfig::Setting &spheres = prims["spheres"];
            for (int i = 0; i < spheres.getLength(); i++) {
                auto p = PrimitiveFactory::create("sphere", spheres[i]);
                applyTranslation(*p, spheres[i]);
                applyRotation(*p, spheres[i]);
                applyScale(*p, spheres[i]);
                scene.addPrimitive(std::move(p));
            }
        }
        if (prims.exists("planes")) {
            const libconfig::Setting &planes = prims["planes"];
            for (int i = 0; i < planes.getLength(); i++) {
                auto p = PrimitiveFactory::create("plane", planes[i]);
                applyTranslation(*p, planes[i]);
                applyRotation(*p, planes[i]);
                applyScale(*p, planes[i]);
                scene.addPrimitive(std::move(p));
            }
        }
        if (prims.exists("cylinders")) {
            const libconfig::Setting &cyls = prims["cylinders"];
            for (int i = 0; i < cyls.getLength(); i++) {
                auto p = PrimitiveFactory::create("cylinder", cyls[i]);
                applyTranslation(*p, cyls[i]);
                applyRotation(*p, cyls[i]);
                applyScale(*p, cyls[i]);
                scene.addPrimitive(std::move(p));
            }
        }
        if (prims.exists("cones")) {
            const libconfig::Setting &cones = prims["cones"];
            for (int i = 0; i < cones.getLength(); i++) {
                auto p = PrimitiveFactory::create("cone", cones[i]);
                applyTranslation(*p, cones[i]);
                applyRotation(*p, cones[i]);
                applyScale(*p, cones[i]);
                scene.addPrimitive(std::move(p));
            }
        }
    }

    static void parseLights(const libconfig::Config &cfg, Scene &scene)
    {
        if (!cfg.exists("lights"))
            return;
        const libconfig::Setting &lights = cfg.lookup("lights");
        if (lights.exists("ambient")) {
            const libconfig::Setting &amb = lights["ambient"];
            if (amb.getType() == libconfig::Setting::TypeGroup)
                scene.addLight(LightFactory::createAmbient(amb));
            else
                scene.addLight(LightFactory::createAmbient((double)amb));
        }
        if (lights.exists("directional")) {
            const libconfig::Setting &dirs = lights["directional"];
            for (int i = 0; i < dirs.getLength(); i++)
                scene.addLight(LightFactory::createDirectional(dirs[i]));
        }
        if (lights.exists("point")) {
            const libconfig::Setting &pts = lights["point"];
            for (int i = 0; i < pts.getLength(); i++)
                scene.addLight(LightFactory::createPoint(pts[i]));
        }
    }

    SceneParser::SceneParser(const std::string &path) : _path(path)
    {
    }

    Scene SceneParser::parse()
    {
        libconfig::Config cfg;
        try {
            cfg.readFile(_path.c_str());
        }
        catch (const libconfig::FileIOException &) {
            throw Exception("cannot open scene file: " + _path);
        }
        catch (const libconfig::ParseException &e) {
            throw Exception(std::string("parse error at line ") + std::to_string(e.getLine()) + ": " + e.getError());
        }

        Scene scene;
        try {
            parseCamera(cfg, scene);
            parsePrimitives(cfg, scene);
            parseLights(cfg, scene);
        }
        catch (const RayTracer::Exception &) {
            throw;
        }
        catch (const libconfig::SettingNotFoundException &e) {
            throw Exception(std::string("missing setting: ") + e.getPath());
        }
        catch (const libconfig::SettingTypeException &e) {
            throw Exception(std::string("wrong type for setting: ") + e.getPath());
        }
        return scene;
    }
}
