cmake_minimum_required(VERSION 3.15)
project(learning)


add_subdirectory(${CMAKE_SOURCE_DIR}/dependencies/GLEW/glew-2.1.0/build/cmake)
add_subdirectory(${CMAKE_SOURCE_DIR}/dependencies/glfw)
include_directories(${CMAKE_SOURCE_DIR}/dependencies/GLEW/glew-2.1.0/include)
include_directories(${CMAKE_SOURCE_DIR}/dependencies/glfw/include)

find_package(OpenGL REQUIRED)

set(CMAKE_BUILD_TYPE "Debug")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_compile_definitions(B_DEBUG)
else()
  add_compile_definitions(B_RELEASE)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCE_FILES
  main.cpp
  renderer.cpp
  indexBuffer.cpp
  vertexBuffer.cpp
  vertexArray.cpp
  vertexBufferLayout.cpp) 
add_executable(run ${SOURCE_FILES})
target_link_libraries(run OpenGL glfw glew)

