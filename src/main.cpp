#include <iostream>
#include <string>

#include "core/Exception.hpp"
#include "core/Renderer.hpp"
#include "core/Scene.hpp"
#include "output/PPMOutput.hpp"
#include "output/SFMLOutput.hpp"
#include "parser/SceneParser.hpp"

static void printUsage(std::ostream &out) {
    out << "USAGE: ./raytracer <SCENE_FILE> [--display|-d]\n"
        << "    SCENE_FILE: scene configuration\n"
        << "    --display, -d: open an SFML window and render live\n";
}

int main(int argc, char **argv) {
    if (argc == 2 && (std::string(argv[1]) == "--help" || std::string(argv[1]) == "-h")) {
        printUsage(std::cout);
        return 0;
    }
    if (argc < 2 || argc > 3) {
        printUsage(std::cerr);
        return 84;
    }

    bool display = false;
    if (argc == 3) {
        std::string flag(argv[2]);
        if (flag == "--display" || flag == "-d")
            display = true;
        else {
            printUsage(std::cerr);
            return 84;
        }
    }

    try {
        RayTracer::Scene scene = RayTracer::SceneParser(argv[1]).parse();
        int w = scene.getWidth();
        int h = scene.getHeight();
        if (display) {
            RayTracer::SFMLOutput out;
            RayTracer::Renderer().render(scene, w, h, out);
        } else {
            RayTracer::PPMOutput out(std::cout);
            RayTracer::Renderer().render(scene, w, h, out);
        }
    } catch (const RayTracer::Exception &e) {
        std::cerr << e.what() << "\n";
        return 84;
    } catch (const std::exception &e) {
        std::cerr << "error: " << e.what() << "\n";
        return 84;
    }
    return 0;
}
