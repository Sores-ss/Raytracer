# Raytracer

A ray tracer written in C++ for the Epitech G-OOP-400 project.

---

## Build

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

The binary `raytracer` is produced at the repo root.

**Dependencies**: `libconfig++`, `SFML 2.6` (optional, for the live window).

---

## Usage

```
./raytracer <scene_file>          render to PPM on stdout
./raytracer <scene_file> --display  render in an SFML window
./raytracer --help                print usage and exit 0
```

### PPM output

```bash
./raytracer scenes/demo_sphere.cfg > output.ppm
```

Open with `feh output.ppm`, `display output.ppm` (ImageMagick), or GIMP.

### SFML live window (`--display` / `-d`)

```bash
./raytracer scenes/demo_sphere.cfg --display
```

Opens an SFML window. Pixels are drawn row by row as they are computed.
Close the window or press **Escape** to stop early.

### Exit codes

| Situation | Exit code |
|---|---|
| Success | 0 |
| Bad arguments / missing scene file / parse error | 84 |

---

## Scene file format

Scene files use the [libconfig](https://hyperrealm.github.io/libconfig/) syntax (`.cfg`).
A scene has three top-level sections: `camera`, `primitives`, and `lights`.

### Camera

```
camera:
{
    resolution  = { width = 800; height = 600; };
    position    = { x = 0; y = 0; z = 0; };
    rotation    = { x = 0; y = 0; z = 0; };
    fieldOfView = 90.0;   // degrees, horizontal
};
```

### Primitives

All primitives accept an optional `translation` block and an optional `rotation` block:

```
translation = { x = 0.0; y = 0.0; z = 0.0; };
rotation    = { x = 0.0; y = 0.0; z = 0.0; };   // degrees around each axis
```

#### Sphere

```
spheres = (
    { x = 0; y = 0; z = -2;  r = 0.5;
      color = { r = 220; g = 50; b = 50; }; }
);
```

| Field | Description |
|---|---|
| `x y z` | Center position |
| `r` | Radius |
| `color` | RGB 0-255 |

#### Plane

```
planes = (
    { axis = "Y"; position = -0.5;
      color = { r = 90; g = 90; b = 200; }; }
);
```

| Field | Description |
|---|---|
| `axis` | `"X"`, `"Y"`, or `"Z"` — normal direction |
| `position` | Offset along that axis |
| `color` | RGB 0-255 |

#### Cylinder (infinite)

```
cylinders = (
    { x = 0; y = 0; z = -3;  r = 0.5;
      axis = { x = 0; y = 1; z = 0; };
      color = { r = 80; g = 180; b = 80; }; }
);
```

| Field | Description |
|---|---|
| `x y z` | Point on the axis |
| `r` | Radius |
| `axis` | Direction vector of the axis |
| `color` | RGB 0-255 |

#### Cone (infinite double cone)

```
cones = (
    { x = 0; y = 0.5; z = -3;  angle = 25.0;
      axis = { x = 0; y = -1; z = 0; };
      color = { r = 210; g = 120; b = 40; }; }
);
```

| Field | Description |
|---|---|
| `x y z` | Apex position |
| `angle` | Half-angle in degrees |
| `axis` | Direction vector of the cone axis |
| `color` | RGB 0-255 |

---

### Lights

#### Ambient

Scalar form (white ambient):
```
ambient = 0.3;
```

Colored form:
```
ambient = { intensity = 0.3; color = { r = 255; g = 240; b = 200; }; };
```

#### Directional

Multiple directional lights are supported. Each may have an optional `color`:

```
directional = (
    { x = 1.0; y = 1.0; z = 0.5; intensity = 0.7; },
    { x = -1.0; y = 0.5; z = 1.0; intensity = 0.9;
      color = { r = 255; g = 40; b = 40; }; }
);
```

| Field | Description |
|---|---|
| `x y z` | Light direction vector |
| `intensity` | 0.0 – 1.0 |
| `color` | Optional RGB 0-255 (default white) |

#### Point light

```
point = (
    { x = 0.0; y = 2.5; z = -3.0; intensity = 1.0;
      color = { r = 255; g = 220; b = 160; }; }
);
```

| Field | Description |
|---|---|
| `x y z` | Light position in world space |
| `intensity` | 0.0 – 1.0 |
| `color` | Optional RGB 0-255 (default white) |

Point lights cast correct shadows: only objects between the light and the hit point block the light.

---

## Demo scenes

| File | What it shows |
|---|---|
| `scenes/demo_sphere.cfg` | Red sphere + blue floor, single directional light |
| `scenes/demo_plane.cfg` | Flat colored plane |
| `scenes/demo_cylinder.cfg` | Infinite cylinder with rotation |
| `scenes/demo_cone.cfg` | Infinite double cone |
| `scenes/demo_shadows.cfg` | Two spheres casting drop shadows on a floor |
| `scenes/demo_colored_lights.cfg` | White sphere lit by three colored directional lights (RGB) |
| `scenes/light_directional.cfg` | Directional light demo |
| `scenes/light_point.cfg` | Three spheres lit by a warm-tinted point light |

---

## Features summary

- **Primitives**: sphere, infinite plane, infinite cylinder, infinite cone
- **Lights**: ambient (white or colored), directional (multiple, colored), point (colored)
- **Shading**: Lambert diffuse, drop shadows
- **Transforms**: translation and rotation (X/Y/Z) per primitive
- **Output**: PPM to stdout (default) or SFML live window (`--display`)
- **Camera**: configurable resolution, position, field of view
