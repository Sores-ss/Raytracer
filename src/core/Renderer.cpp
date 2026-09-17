#include "core/Renderer.hpp"

namespace RayTracer {

void Renderer::render(const Scene &scene, int width, int height, IRenderOutput &out) const {
    const Camera &cam = scene.getCamera();
    out.begin(width, height);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            double u = static_cast<double>(x) / (width - 1);
            double v = 1.0 - static_cast<double>(y) / (height - 1);
            Ray r = cam.ray(u, v);

            double t;
            IPrimitive *hit = nullptr;
            if (!scene.hits(r, t, hit)) {
                out.writePixel(x, y, Math::Vector3D(0, 0, 0));
                continue;
            }

            Math::Point3D P = r.origin + r.direction * t;
            Math::Vector3D normal = hit->getNormalAt(P);

            Math::Vector3D light(0, 0, 0);
            for (const auto &l : scene.getLights()) {
                Math::Vector3D sdir = l->shadowDir();
                if (sdir.length() > 1e-9) {
                    Ray shadowRay(P + normal * 1e-4, sdir);
                    double shadowT;
                    IPrimitive *shadowHit = nullptr;
                    if (scene.hits(shadowRay, shadowT, shadowHit))
                        continue;
                }
                light += l->illuminate(P, normal);
            }

            out.writePixel(x, y, light * hit->getColor());
        }
        out.endRow(y);
    }
    out.finish();
}

}
