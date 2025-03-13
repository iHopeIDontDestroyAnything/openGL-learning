cmake_minimum_required(VERSION 3.15)
project(learning)


add_subdirectory(${CMAKE_SOURCE_DIR}/dependencies/GLEW/glew-2.1.0/build/cmake)
include_directories(${CMAKE_SOURCE_DIR}/dependencies/GLEW/glew-2.1.0/include)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCE_FILES
  main.cpp
  ) 
add_executable(run ${SOURCE_FILES})
target_link_libraries(run OpenGL glfw glew)

