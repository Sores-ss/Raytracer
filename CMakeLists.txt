cmake_minimum_required(VERSION 3.17)
project(raytracer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBCONFIG REQUIRED libconfig++)

if(NOT DEFINED SFML_DIR)
    set(SFML_DIR "/opt/sfml2/lib/cmake/SFML")
endif()
find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

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
    src/primitives/Cylinder.cpp
    src/primitives/Cone.cpp
    src/primitives/Triangle.cpp
    src/primitives/ISdf.cpp
    src/primitives/Mandelbulb.cpp
    src/lights/ALight.cpp
    src/lights/AmbientLight.cpp
    src/lights/DirectionalLight.cpp
    src/lights/PointLight.cpp
    src/parser/SceneParser.cpp
    src/factory/PrimitiveFactory.cpp
    src/factory/LightFactory.cpp
    src/output/PPMOutput.cpp
    src/output/SFMLOutput.cpp
)

target_include_directories(raytracer PRIVATE src ${LIBCONFIG_INCLUDE_DIRS} /opt/sfml2/include)
target_link_libraries(raytracer PRIVATE ${LIBCONFIG_LIBRARIES} sfml-graphics sfml-window sfml-system)
target_compile_options(raytracer PRIVATE ${LIBCONFIG_CFLAGS_OTHER})
