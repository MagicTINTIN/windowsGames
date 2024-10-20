cmake_minimum_required(VERSION 3.16)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
project(pirawin)

set(CMAKE_CXX_STANDARD 17)

include_directories(
   include
   ../dependencies/glad
)

FILE(GLOB SRC_FILES src/**.c src/**.cc src/**.cpp)
#to add source files manually:
#set(SRC_FILES
#   src/main.c
#)

add_library(glad ../dependencies/glad/glad.c)

add_executable(${CMAKE_PROJECT_NAME} src/main.cc)
target_link_libraries(${CMAKE_PROJECT_NAME} glad glfw)
target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${SRC_FILES})