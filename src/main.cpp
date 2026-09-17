#include <iostream>

#include "core/Exception.hpp"
#include "core/Renderer.hpp"
#include "core/Scene.hpp"
#include "parser/SceneParser.hpp"

static void printUsage(std::ostream &out) {
    out << "USAGE: ./raytracer <SCENE_FILE>\n"
        << "    SCENE_FILE: scene configuration\n";
}

int main(int argc, char **argv) {
    if (argc == 2 && (std::string(argv[1]) == "--help" || std::string(argv[1]) == "-h")) {
        printUsage(std::cout);
        return 0;
    }
    if (argc != 2) {
        printUsage(std::cerr);
        return 84;
    }
    try {
        RayTracer::Scene scene = RayTracer::SceneParser(argv[1]).parse();
        RayTracer::Renderer().render(scene, scene.getWidth(), scene.getHeight());
    } catch (const RayTracer::Exception &e) {
        std::cerr << e.what() << "\n";
        return 84;
    } catch (const std::exception &e) {
        std::cerr << "error: " << e.what() << "\n";
        return 84;
    }
    return 0;
}
