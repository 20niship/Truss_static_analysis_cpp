cmake_minimum_required(VERSION 3.0)
project(TrussAnalysis)

set(CMAKE_CXX_STANDARD 17)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(ImGui REQUIRED)
find_package(Freetype REQUIRED)

# glob sources, source1, source2, ...
file(GLOB SOURCES1 "src/*.cpp")
file(GLOB SOURCES2 "src/geometry_store/*.cpp")
file(GLOB SOURCES3 "src/geometry_store/buffers/*.cpp")
file(GLOB SOURCES4 "src/geometry_store/shaders/*.cpp")
file(GLOB SOURCES5 "src/geometry_store/solver/*.cpp")

file(GLOB SOURCES6 "src/ImGui/*.cpp")


