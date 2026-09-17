/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-7
** File description:
** Renderer
*/

#include "core/Renderer.hpp"

#include <vector>
#include <thread>
#include <random>
#include <chrono>

namespace RayTracer
{
    Renderer::Renderer(int samples, int threads) : _samplesPerAxis(std::max(1, samples)), _threads(std::max(1, threads)) {}

    void Renderer::render(const Scene &scene, int width, int height, IRenderOutput &out) const
    {
        const Camera &cam = scene.getCamera();
        out.begin(width, height);

        std::vector<Math::Vector3D> buffer(width * height, Math::Vector3D(0, 0, 0));

        auto worker = [&](int id){
            std::mt19937 rng(static_cast<unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count()) + id);
            std::uniform_real_distribution<double> dist(0.0, 1.0);
            for (int y = id; y < height; y += _threads) {
                for (int x = 0; x < width; x++) {
                    Math::Vector3D accum(0, 0, 0);
                    if (_samplesPerAxis <= 1) {
                        double u = static_cast<double>(x) / (width - 1);
                        double v = 1.0 - static_cast<double>(y) / (height - 1);
                        Ray r = cam.ray(u, v);
                        double t;
                        IPrimitive *hit = nullptr;
                        if (!scene.hits(r, t, hit)) {
                            accum = Math::Vector3D(0, 0, 0);
                        } else {
                            Math::Point3D P = r.origin + r.direction * t;
                            Math::Vector3D normal = hit->getNormalAt(P);
                            Math::Vector3D light(0, 0, 0);
                            for (const auto &l : scene.getLights()) {
                                Math::Vector3D sdir = l->shadowDir(P);
                                if (sdir.length() > 1e-9) {
                                    Ray shadowRay(P + normal * 1e-4, sdir);
                                    double shadowT;
                                    IPrimitive *shadowHit = nullptr;
                                    if (scene.hits(shadowRay, shadowT, shadowHit) && shadowT < l->shadowMaxDistance(P))
                                        continue;
                                }
                                light += l->illuminate(P, normal);
                            }
                            accum = light * hit->getColor();
                        }
                    } else {
                        int ss = _samplesPerAxis;
                        for (int sy = 0; sy < ss; ++sy) {
                            for (int sx = 0; sx < ss; ++sx) {
                                double u = (x + (sx + dist(rng)) / static_cast<double>(ss)) / (width - 1);
                                double v = 1.0 - (y + (sy + dist(rng)) / static_cast<double>(ss)) / (height - 1);
                                Ray r = cam.ray(u, v);
                                double t;
                                IPrimitive *hit = nullptr;
                                if (!scene.hits(r, t, hit)) {
                                    continue;
                                }
                                Math::Point3D P = r.origin + r.direction * t;
                                Math::Vector3D normal = hit->getNormalAt(P);
                                Math::Vector3D light(0, 0, 0);
                                for (const auto &l : scene.getLights()) {
                                    Math::Vector3D sdir = l->shadowDir(P);
                                    if (sdir.length() > 1e-9) {
                                        Ray shadowRay(P + normal * 1e-4, sdir);
                                        double shadowT;
                                        IPrimitive *shadowHit = nullptr;
                                        if (scene.hits(shadowRay, shadowT, shadowHit) && shadowT < l->shadowMaxDistance(P))
                                            continue;
                                    }
                                    light += l->illuminate(P, normal);
                                }
                                accum += light * hit->getColor();
                            }
                        }
                        accum = accum / static_cast<double>(ss * ss);
                    }
                    buffer[y * width + x] = accum;
                }
            }
        };

        std::vector<std::thread> threads;
        for (int i = 0; i < _threads; ++i)
            threads.emplace_back(worker, i);
        for (auto &t : threads)
            t.join();

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                out.writePixel(x, y, buffer[y * width + x]);
            }
            out.endRow(y);
        }
        out.finish();
    }

}
