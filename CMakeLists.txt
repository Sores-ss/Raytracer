cmake_minimum_required(VERSION 3.17)
project(raytracer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBCONFIG REQUIRED libconfig++)

add_executable(raytracer
    src/main.cpp
    src/math/Vector3D.cpp
    src/math/Point3D.cpp
    src/math/Rectangle3D.cpp
    src/core/Ray.cpp
    src/core/Camera.cpp
    src/core/Scene.cpp
    src/core/Renderer.cpp
    src/primitives/APrimitive.cpp
    src/primitives/Sphere.cpp
    src/primitives/Plane.cpp
    src/lights/ALight.cpp
    src/lights/AmbientLight.cpp
    src/lights/DirectionalLight.cpp
    src/parser/SceneParser.cpp
    src/factory/PrimitiveFactory.cpp
    src/factory/LightFactory.cpp
)

target_include_directories(raytracer PRIVATE src ${LIBCONFIG_INCLUDE_DIRS})
target_link_libraries(raytracer PRIVATE ${LIBCONFIG_LIBRARIES})
target_compile_options(raytracer PRIVATE ${LIBCONFIG_CFLAGS_OTHER})
