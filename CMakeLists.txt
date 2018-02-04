cmake_minimum_required(VERSION 3.7)
project(TEngine C)

set(CMAKE_C_STANDARD 11)

set(DEPENDENCIES_DIR ${CMAKE_SOURCE_DIR}/dependencies/)

include_directories(${DEPENDENCIES_DIR}sdl2/include/)
include_directories(${DEPENDENCIES_DIR}glew/include/)

#define RELEASE_BUILD   //release build
#define DEBUG_BUILD     //debug build

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")

if(${CMAKE_BUILD_TYPE} STREQUAL Release)
    add_definitions("-DRELEASE_BUILD")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mwindows -Wall -Wextra -pedantic")
elseif(${CMAKE_BUILD_TYPE} STREQUAL Debug)
    add_definitions("-DDEBUG_BUILD")
endif()

add_executable(TEngine src/model.c src/texture.c src/render.c src/tinyobj_loader_c.h src/main.c src/lodepng.c src/linmath.h src/display.c src/display.h src/master.h src/utils.c src/utils.h src/program.c src/program.h src/camera.c src/camera.h src/mesh.c src/mesh.h src/light.c src/light.h src/filehelper.c src/filehelper.h)

target_link_libraries(${PROJECT_NAME} C:/MinGW/lib/libopengl32.a)
target_link_libraries(${PROJECT_NAME} ${DEPENDENCIES_DIR}glew/lib/libGLEW_2.dll.a)
target_link_libraries(${PROJECT_NAME} ${DEPENDENCIES_DIR}sdl2/lib/libSDL2main.a)
target_link_libraries(${PROJECT_NAME} ${DEPENDENCIES_DIR}sdl2/lib/libSDL2.dll.a)