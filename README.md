# TEngine

A game engine written in C using OpenGL.

## How to use
Compile using CMake (3.9 or greater).

## Development
In order to make development easier pass the following flag to CMake
```
 -DTENGINE_TESTAPP=true 
```
The project will now be compiled as an executable. The file ```demo.c``` contains the ```main()``` where you can place your code. 

## Libraries
Uses:
* [lodepng](https://github.com/lvandeve/lodepng)
* [tinyobjloader-c](https://github.com/syoyo/tinyobjloader-c)
* [linmath.h](https://github.com/datenwolf/linmath.h)

Dependencies:
* [SDL2](https://www.libsdl.org/)
* [GLEW](http://glew.sourceforge.net/)

## License
MIT License
