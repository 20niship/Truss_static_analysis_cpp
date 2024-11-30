cmake_minimum_required(VERSION 3.22)
project(TrussAnalysis)

# export compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# force colored output
add_compile_options(-fdiagnostics-color=always)

set(CMAKE_CXX_STANDARD 17)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(Freetype REQUIRED)
find_package(Eigen3 REQUIRED)

# glob sources, source1, source2, ...
file(GLOB SOURCES1 "src/*.cpp")
file(GLOB SOURCES2 "src/geometry_store/*.cpp")
file(GLOB SOURCES3 "src/geometry_store/buffers/*.cpp")
file(GLOB SOURCES4 "src/geometry_store/shaders/*.cpp")
file(GLOB SOURCES5 "src/geometry_store/solver/*.cpp")
file(GLOB SOURCES6 "ImGui/*.cpp")

# copy Images folder to build directory
file(COPY Images DESTINATION ${CMAKE_BINARY_DIR})
file(COPY src/geometry_store/shaders DESTINATION ${CMAKE_BINARY_DIR}/src/geometry_store)

add_executable(TrussAnalysis ${SOURCES1} ${SOURCES2} ${SOURCES3} ${SOURCES4} ${SOURCES5} ${SOURCES6}
  main.cpp
  cocoa_file_dialog.mm
)

target_include_directories(TrussAnalysis PRIVATE 
  ${CMAKE_CURRENT_SOURCE_DIR}/
  ${OPENGL_INCLUDE_DIR}
  ${GLEW_INCLUDE_DIRS} 
  ${EIGEN3_INCLUDE_DIR}
  ${GLFW_INCLUDE_DIRS} 
  ${GLM_INCLUDE_DIRS} 
  ${FREETYPE_INCLUDE_DIRS}
)

target_link_libraries(TrussAnalysis #   
  ${OPENGL_LIBRARIES} 
  ${GLEW_LIBRARY} 
  GLEW
  glfw 
  "-framework OpenGL"
  "-framework Cocoa"
  ${FREETYPE_LIBRARIES})

target_link_directories(TrussAnalysis PRIVATE 
  ${GLEW_LIBRARY_DIRS}
  /opt/homebrew/lib
  /usr/local/lib
)


