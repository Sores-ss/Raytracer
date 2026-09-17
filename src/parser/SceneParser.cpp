#include "parser/SceneParser.hpp"

#include <cmath>

#include <libconfig.h++>

#include "core/Exception.hpp"
#include "factory/LightFactory.hpp"
#include "factory/PrimitiveFactory.hpp"
#include "math/Rectangle3D.hpp"

namespace RayTracer {

static const double PI = 3.14159265358979323846;

// libconfig stores integer literals as TypeInt; this handles both int and float values
static double asDouble(const libconfig::Setting &s) {
    if (s.getType() == libconfig::Setting::TypeInt)
        return static_cast<int>(s);
    return static_cast<double>(s);
}

static void parseCamera(const libconfig::Config &cfg, Scene &scene) {
    const libconfig::Setting &cam = cfg.lookup("camera");
    int w = (int)cam["resolution"]["width"];
    int h = (int)cam["resolution"]["height"];
    scene.setResolution(w, h);

    double px = asDouble(cam["position"]["x"]);
    double py = asDouble(cam["position"]["y"]);
    double pz = asDouble(cam["position"]["z"]);
    double fov = asDouble(cam["fieldOfView"]);

    double aspect = static_cast<double>(w) / h;
    double halfH = std::tan(fov / 2.0 * PI / 180.0);
    double halfW = aspect * halfH;

    Camera c;
    c.origin = Math::Point3D(px, py, pz);
    c.screen = Math::Rectangle3D(
        Math::Point3D(px - halfW, py - halfH, pz - 1.0),
        Math::Vector3D(2.0 * halfW, 0, 0),
        Math::Vector3D(0, 2.0 * halfH, 0));
    scene.setCamera(c);
}

static void parsePrimitives(const libconfig::Config &cfg, Scene &scene) {
    if (!cfg.exists("primitives"))
        return;
    const libconfig::Setting &prims = cfg.lookup("primitives");
    if (prims.exists("spheres")) {
        const libconfig::Setting &spheres = prims["spheres"];
        for (int i = 0; i < spheres.getLength(); i++)
            scene.addPrimitive(PrimitiveFactory::create("sphere", spheres[i]));
    }
    if (prims.exists("planes")) {
        const libconfig::Setting &planes = prims["planes"];
        for (int i = 0; i < planes.getLength(); i++)
            scene.addPrimitive(PrimitiveFactory::create("plane", planes[i]));
    }
}

static void parseLights(const libconfig::Config &cfg, Scene &scene) {
    if (!cfg.exists("lights"))
        return;
    const libconfig::Setting &lights = cfg.lookup("lights");
    if (lights.exists("ambient")) {
        double intensity = (double)lights["ambient"];
        scene.addLight(LightFactory::createAmbient(intensity));
    }
    if (lights.exists("directional")) {
        const libconfig::Setting &dirs = lights["directional"];
        for (int i = 0; i < dirs.getLength(); i++)
            scene.addLight(LightFactory::createDirectional(dirs[i]));
    }
    // TODO: point lights
}

SceneParser::SceneParser(const std::string &path) : _path(path) {}

Scene SceneParser::parse() {
    libconfig::Config cfg;
    try {
        cfg.readFile(_path.c_str());
    } catch (const libconfig::FileIOException &) {
        throw Exception("cannot open scene file: " + _path);
    } catch (const libconfig::ParseException &e) {
        throw Exception(std::string("parse error at line ")
            + std::to_string(e.getLine()) + ": " + e.getError());
    }

    Scene scene;
    try {
        parseCamera(cfg, scene);
        parsePrimitives(cfg, scene);
        parseLights(cfg, scene);
    } catch (const RayTracer::Exception &) {
        throw;
    } catch (const libconfig::SettingNotFoundException &e) {
        throw Exception(std::string("missing setting: ") + e.getPath());
    } catch (const libconfig::SettingTypeException &e) {
        throw Exception(std::string("wrong type for setting: ") + e.getPath());
    }
    return scene;
}

}
