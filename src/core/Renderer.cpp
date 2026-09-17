#include "core/Renderer.hpp"

#include <algorithm>
#include <iostream>

namespace RayTracer {

static void writePixel(const Math::Vector3D &c) {
    int r = static_cast<int>(std::clamp(c.x, 0.0, 1.0) * 255);
    int g = static_cast<int>(std::clamp(c.y, 0.0, 1.0) * 255);
    int b = static_cast<int>(std::clamp(c.z, 0.0, 1.0) * 255);
    std::cout << r << " " << g << " " << b << "\n";
}

void Renderer::render(const Scene &scene, int width, int height) const {
    const Camera &cam = scene.getCamera();
    std::cout << "P3\n" << width << " " << height << "\n255\n";

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            double u = static_cast<double>(x) / (width - 1);
            double v = 1.0 - static_cast<double>(y) / (height - 1);
            Ray r = cam.ray(u, v);

            double t;
            IPrimitive *hit = nullptr;
            if (!scene.hits(r, t, hit)) {
                writePixel(Math::Vector3D(0, 0, 0));
                continue;
            }

            Math::Point3D P = r.origin + r.direction * t;
            Math::Vector3D normal = hit->getNormalAt(P);

            Math::Vector3D light(0, 0, 0);
            for (const auto &l : scene.getLights())
                light += l->illuminate(P, normal);

            writePixel(light * hit->getColor());
        }
    }
}

}
