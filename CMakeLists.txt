cmake_minimum_required(VERSION 3.16)
project(exe)
option(NIXOS "Dont try to compile GLFW on nixos, just link it" OFF)

if(NIXOS)
link_libraries(GL glfw)
else()
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(dependencies/glfw)
endif()


include_directories(
   include
   dependencies/glad
)
add_library(glad dependencies/glad/glad.c)

add_subdirectory(pyrawin)
add_subdirectory(tetrawin)