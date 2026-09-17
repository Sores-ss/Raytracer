#include <iostream>
#include <string>

#include "core/Exception.hpp"
#include "core/Renderer.hpp"
#include "core/Scene.hpp"
#include "output/PPMOutput.hpp"
#include "output/SFMLOutput.hpp"
#include "parser/SceneParser.hpp"

static void printUsage(std::ostream &out)
{
    out << "USAGE: ./raytracer <SCENE_FILE> [options]\n";
    out << "    SCENE_FILE: scene configuration\n";
    out << "    --display, -d       : open an SFML window and render live\n";
    out << "    --samples N         : supersampling N per axis (1 = no AA, 2 = 4 samples)\n";
    out << "    --threads N         : number of render worker threads\n";
}

int main(int argc, char **argv)
{
    if (argc == 2 && (std::string(argv[1]) == "--help" || std::string(argv[1]) == "-h")) {
        printUsage(std::cout);
        return 0;
    }
    if (argc < 2) {
        printUsage(std::cerr);
        return 84;
    }
    bool display = false;
    int samples = 1;
    int threads = 1;
    // Simple argv parsing for supported flags
    std::string scenePath = argv[1];
    for (int i = 2; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--display" || arg == "-d") {
            display = true;
            continue;
        }
        if (arg == "--samples") {
            if (i + 1 >= argc) { printUsage(std::cerr); return 84; }
            samples = std::stoi(argv[++i]);
            if (samples < 1) samples = 1;
            continue;
        }
        if (arg == "--threads") {
            if (i + 1 >= argc) { printUsage(std::cerr); return 84; }
            threads = std::stoi(argv[++i]);
            if (threads < 1) threads = 1;
            continue;
        }
        printUsage(std::cerr);
        return 84;
    }
    try {
        RayTracer::Scene scene = RayTracer::SceneParser(scenePath).parse();
        int w = scene.getWidth();
        int h = scene.getHeight();
        if (display) {
            RayTracer::SFMLOutput out;
            RayTracer::Renderer renderer(samples, threads);
            renderer.render(scene, w, h, out);
        } else {
            RayTracer::PPMOutput out(std::cout);
            RayTracer::Renderer renderer(samples, threads);
            renderer.render(scene, w, h, out);
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
