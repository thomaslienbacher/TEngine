cmake_minimum_required(VERSION 3.9)
project(TEngine C)

set(CMAKE_C_STANDARD 11)

#depending on build type RELEASE_BUILD or DEBUG_BUILD are defined
if (${CMAKE_BUILD_TYPE} STREQUAL Release)
    add_definitions("-DRELEASE_BUILD")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mwindows -Wall -Wextra")
elseif (${CMAKE_BUILD_TYPE} STREQUAL Debug)
    add_definitions("-DDEBUG_BUILD")
endif ()

if (${TENGINE_TESTAPP})
    set(BUILD_USAGE TestApp)
else ()
    set(BUILD_USAGE Library)
endif ()

message("Building TEngine as ${BUILD_USAGE} in ${CMAKE_BUILD_TYPE}")

set(SOURCES src/model.c src/texture.c src/render.c src/lodepng.c src/tengine_math.h src/display.c src/display.h src/master.h src/utils.c src/utils.h src/program.c src/program.h src/camera.c src/camera.h src/mesh.c src/mesh.h src/light.c src/light.h src/filehelper.c src/filehelper.h src/tengine_math.c src/vector.c src/vector.h src/framebuffer.c src/framebuffer.h src/frustum.c src/frustum.h src/text.c src/text.h)

if (${BUILD_USAGE} STREQUAL TestApp)
    add_executable(TEngine src/demo.c ${SOURCES})
elseif (${BUILD_USAGE} STREQUAL Library)
    add_library(TEngine ${SOURCES})
endif ()

find_package(PkgConfig REQUIRED)
find_package(OpenGL REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2 SDL2_ttf)
pkg_check_modules(GLEW REQUIRED glew)

target_include_directories(TEngine PUBLIC ${SDL2_INCLUDE_DIRS})
target_include_directories(TEngine PUBLIC ${GLEW_INCLUDE_DIRS})

target_link_libraries(TEngine ${OPENGL_LIBRARIES})
target_link_libraries(TEngine ${GLEW_LIBRARIES})
target_link_libraries(TEngine ${SDL2_LIBRARIES})
