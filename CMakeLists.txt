cmake_minimum_required(VERSION 3.9)
project(TEngine C)

set(CMAKE_C_STANDARD 11)

set(DEPENDENCIES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/)

include_directories(${DEPENDENCIES_DIR}sdl2/include/)
include_directories(${DEPENDENCIES_DIR}glew/include/)

#define RELEASE_BUILD   //release build
#define DEBUG_BUILD     //debug build

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")

if(${CMAKE_BUILD_TYPE} STREQUAL Release)
    add_definitions("-DRELEASE_BUILD")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mwindows -Wall -Wextra")
elseif(${CMAKE_BUILD_TYPE} STREQUAL Debug)
    add_definitions("-DDEBUG_BUILD")
endif()

if(NOT DEFINED TENGINE_BUILD_USAGE)
    set(BUILD_USAGE TestApp)
else()
    set(BUILD_USAGE Library)
endif()

message("Building TEngine as " ${BUILD_USAGE})

set(SOURCES src/model.c src/texture.c src/render.c src/tinyobj_loader_c.h src/lodepng.c src/tengine_math.h src/display.c src/display.h src/master.h src/utils.c src/utils.h src/program.c src/program.h src/camera.c src/camera.h src/mesh.c src/mesh.h src/light.c src/light.h src/filehelper.c src/filehelper.h src/tengine_math.c src/vector.c src/vector.h src/framebuffer.c src/framebuffer.h src/frustum.c src/frustum.h)

if(${BUILD_USAGE} STREQUAL TestApp)
    add_executable(TEngine src/main.c ${SOURCES})
elseif(${BUILD_USAGE} STREQUAL Library)
    add_library(TEngine ${SOURCES})
endif()

target_link_libraries(${PROJECT_NAME} C:/MinGW/lib/libopengl32.a)
target_link_libraries(${PROJECT_NAME} ${DEPENDENCIES_DIR}glew/lib/libGLEW_2.dll.a)
target_link_libraries(${PROJECT_NAME} ${DEPENDENCIES_DIR}sdl2/lib/libSDL2main.a)
target_link_libraries(${PROJECT_NAME} ${DEPENDENCIES_DIR}sdl2/lib/libSDL2.dll.a)