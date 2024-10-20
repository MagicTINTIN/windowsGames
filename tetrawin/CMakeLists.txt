cmake_minimum_required(VERSION 3.16)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
project(tetrawin)
set(SUBPROJECT_NAME "tetrawin")

set(CMAKE_CXX_STANDARD 17)

FILE(GLOB SRC_FILES src/**.c src/**.cc src/**.cpp)
#to add source files manually:
#set(SRC_FILES
#   src/main.c
#)

add_executable(${SUBPROJECT_NAME} src/main.cc)
target_link_libraries(${SUBPROJECT_NAME} glad glfw)
target_sources(${SUBPROJECT_NAME} PRIVATE ${SRC_FILES})