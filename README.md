# Raytracer

A ray tracer written in C++ for the Epitech G-OOP-400 project.

## Compile

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

The binary `raytracer` is produced at the repo root.

## Run

```bash
./raytracer <scene_file>
./raytracer --help
```

Output is a PPM image written to stdout:

```bash
./raytracer scenes/demo_sphere.cfg > output.ppm
```
