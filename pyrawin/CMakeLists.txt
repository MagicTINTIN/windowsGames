cmake_minimum_required(VERSION 3.16)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
project(pyrawin)
set(SUBPROJECT_NAME "pyrawin")

set(CMAKE_CXX_STANDARD 17)

# include_directories(
#    include
#    ../dependencies/glad
# )

FILE(GLOB SRC_FILES src/**.c src/**.cc src/**.cpp)
#to add source files manually:
#set(SRC_FILES
#   src/main.c
#)

# add_library(glad ../dependencies/glad/glad.c)

add_executable(${SUBPROJECT_NAME} src/main.cc)
target_link_libraries(${SUBPROJECT_NAME} glad glfw)
target_sources(${SUBPROJECT_NAME} PRIVATE ${SRC_FILES})