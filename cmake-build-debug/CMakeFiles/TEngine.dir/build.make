# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.12

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2018.2.4\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2018.2.4\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Eigene Dateien\Programmieren\C\CLion-Workspace\TEngine"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Eigene Dateien\Programmieren\C\CLion-Workspace\TEngine\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/TEngine.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/TEngine.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TEngine.dir/flags.make

CMakeFiles/TEngine.dir/src/main.c.obj: CMakeFiles/TEngine.dir/flags.make
CMakeFiles/TEngine.dir/src/main.c.obj: CMakeFiles/TEngine.dir/includes_C.rsp
CMakeFiles/TEngine.dir/src/main.c.obj: ../src/main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Eigene Dateien\Programmieren\C\CLion-Workspace\TEngine\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/TEngine.dir/src/main.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\TEngine.dir\src\main.c.obj   -c "C:\Eigene Dateien\Programmieren\C\CLion-Workspace\TEngine\src\main.c"

CMakeFiles/TEngine.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TEngine.dir/src/main.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:\Eigene Dateien\Programmieren\C\CLion-Workspace\TEngine\src\main.c" > CMakeFiles\TEngine.dir\src\main.c.i

CMakeFiles/TEngine.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TEngine.dir/src/main.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "C:\Eigene Dateien\Programmieren\C\CLion-Workspace\TEngine\src\main.c" -o CMakeFiles\TEngine.dir\src\main.c.s

CMakeFiles/TEngine.dir/src/model.c.obj: CMakeFiles/TEngine.dir/flags.make
CMakeFiles/TEngine.dir/src/model.c.obj: CMakeFiles/TEngine.dir/includes_C.rsp
CMakeFiles/TEngine.dir/src/model.c.obj: ../src/model.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Eigene Dateien\Programmieren\C\CLion-Workspace\TEngine\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/TEngine.dir/src/model.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\TEngine.dir\src\model.c.obj   -c "C:\Eigene Dateien\Programmieren\C\CLion-Workspace\TEngine\src\model.c"

CMakeFiles/TEngine.dir/src/model.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TEngine.dir/src/model.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:\Eigene Dateien\Programmieren\C\CLion-Workspace\TEngine\src\model.c" > CMakeFiles\TEngine.dir\src\model.c.i

CMakeFiles/TEngine.dir/src/model.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TEngine.dir/src/model.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "C:\Eigene Dateien\Programmieren\C\CLion-Workspace\TEngine\src\model.c" -o CMakeFiles\TEngine.dir\src\model.c.s

CMakeFiles/TEngine.dir/src/texture.c.obj: CMakeFiles/TEngine.dir/flags.make
CMakeFiles/TEngine.dir/src/texture.c.obj: CMakeFiles/TEngine.dir/includes_C.rsp
CMakeFiles/TEngine.dir/src/texture.c.obj: ../src/texture.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Eigene Dateien\Programmieren\C\CLion-Workspace\TEngine\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/TEngine.dir/src/texture.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\TEngine.dir\src\texture.c.obj   -c "C:\Eigene Dateien\Programmieren\C\CLion-Workspace\TEngine\src\texture.c"

CMakeFiles/TEngine.dir/src/texture.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TEngine.dir/src/texture.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:\Eigene Dateien\Programmieren\C\CLion-Workspace\TEngine\src\texture.c" > CMakeFiles\TEngine.dir\src\texture.c.i

CMakeFiles/TEngine.dir/src/texture.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TEngine.dir/src/texture.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "C:\Eigene Dateien\Programmieren\C\CLion-Workspace\TEngine\src\texture.c" -o CMakeFiles\TEngine.dir\src\texture.c.s

CMakeFiles/TEngine.dir/src/render.c.obj: CMakeFiles/TEngine.dir/flags.make
CMakeFiles/TEngine.dir/src/render.c.obj: CMakeFiles/TEngine.dir/includes_C.rsp
CMakeFiles/TEngine.dir/src/render.c.obj: ../src/render.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Eigene Dateien\Programmieren\C\CLion-Workspace\TEngine\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/TEngine.dir/src/render.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\TEngine.dir\src\render.c.obj   -c "C:\Eigene Dateien\Programmieren\C\CLion-Workspace\TEngine\src\render.c"

CMakeFiles/TEngine.dir/src/render.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TEngine.dir/src/render.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:\Eigene Dateien\Programmieren\C\CLion-Workspace\TEngine\src\render.c" > CMakeFiles\TEngine.dir\src\render.c.i

CMakeFiles/TEngine.dir/src/render.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TEngine.dir/src/render.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "C:\Eigene Dateien\Programmieren\C\CLion-Workspace\TEngine\src\render.c" -o CMakeFiles\TEngine.dir\src\render.c.s

CMakeFiles/TEngine.dir/src/lodepng.c.obj: CMakeFiles/TEngine.dir/flags.make
CMakeFiles/TEngine.dir/src/lodepng.c.obj: CMakeFiles/TEngine.dir/includes_C.rsp
CMakeFiles/TEngine.dir/src/lodepng.c.obj: ../src/lodepng.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Eigene Dateien\Programmieren\C\CLion-Workspace\TEngine\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/TEngine.dir/src/lodepng.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\TEngine.dir\src\lodepng.c.obj   -c "C:\Eigene Dateien\Programmieren\C\CLion-Workspace\TEngine\src\lodepng.c"

CMakeFiles/TEngine.dir/src/lodepng.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TEngine.dir/src/lodepng.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:\Eigene Dateien\Programmieren\C\CLion-Workspace\TEngine\src\lodepng.c" > CMakeFiles\TEngine.dir\src\lodepng.c.i

CMakeFiles/TEngine.dir/src/lodepng.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TEngine.dir/src/lodepng.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "C:\Eigene Dateien\Programmieren\C\CLion-Workspace\TEngine\src\lodepng.c" -o CMakeFiles\TEngine.dir\src\lodepng.c.s

CMakeFiles/TEngine.dir/src/display.c.obj: CMakeFiles/TEngine.dir/flags.make
CMakeFiles/TEngine.dir/src/display.c.obj: CMakeFiles/TEngine.dir/includes_C.rsp
CMakeFiles/TEngine.dir/src/display.c.obj: ../src/display.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Eigene Dateien\Programmieren\C\CLion-Workspace\TEngine\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/TEngine.dir/src/display.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\TEngine.dir\src\display.c.obj   -c "C:\Eigene Dateien\Programmieren\C\CLion-Workspace\TEngine\src\display.c"

CMakeFiles/TEngine.dir/src/display.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TEngine.dir/src/display.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:\Eigene Dateien\Programmieren\C\CLion-Workspace\TEngine\src\display.c" > CMakeFiles\TEngine.dir\src\display.c.i

CMakeFiles/TEngine.dir/src/display.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TEngine.dir/src/display.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "C:\Eigene Dateien\Programmieren\C\CLion-Workspace\TEngine\src\display.c" -o CMakeFiles\TEngine.dir\src\display.c.s

CMakeFiles/TEngine.dir/src/utils.c.obj: CMakeFiles/TEngine.dir/flags.make
CMakeFiles/TEngine.dir/src/utils.c.obj: CMakeFiles/TEngine.dir/includes_C.rsp
CMakeFiles/TEngine.dir/src/utils.c.obj: ../src/utils.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Eigene Dateien\Programmieren\C\CLion-Workspace\TEngine\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/TEngine.dir/src/utils.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\TEngine.dir\src\utils.c.obj   -c "C:\Eigene Dateien\Programmieren\C\CLion-Workspace\TEngine\src\utils.c"

CMakeFiles/TEngine.dir/src/utils.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TEngine.dir/src/utils.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:\Eigene Dateien\Programmieren\C\CLion-Workspace\TEngine\src\utils.c" > CMakeFiles\TEngine.dir\src\utils.c.i

CMakeFiles/TEngine.dir/src/utils.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TEngine.dir/src/utils.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "C:\Eigene Dateien\Programmieren\C\CLion-Workspace\TEngine\src\utils.c" -o CMakeFiles\TEngine.dir\src\utils.c.s

CMakeFiles/TEngine.dir/src/program.c.obj: CMakeFiles/TEngine.dir/flags.make
CMakeFiles/TEngine.dir/src/program.c.obj: CMakeFiles/TEngine.dir/includes_C.rsp
CMakeFiles/TEngine.dir/src/program.c.obj: ../src/program.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Eigene Dateien\Programmieren\C\CLion-Workspace\TEngine\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/TEngine.dir/src/program.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\TEngine.dir\src\program.c.obj   -c "C:\Eigene Dateien\Programmieren\C\CLion-Workspace\TEngine\src\program.c"

CMakeFiles/TEngine.dir/src/program.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TEngine.dir/src/program.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:\Eigene Dateien\Programmieren\C\CLion-Workspace\TEngine\src\program.c" > CMakeFiles\TEngine.dir\src\program.c.i

CMakeFiles/TEngine.dir/src/program.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TEngine.dir/src/program.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "C:\Eigene Dateien\Programmieren\C\CLion-Workspace\TEngine\src\program.c" -o CMakeFiles\TEngine.dir\src\program.c.s

CMakeFiles/TEngine.dir/src/camera.c.obj: CMakeFiles/TEngine.dir/flags.make
CMakeFiles/TEngine.dir/src/camera.c.obj: CMakeFiles/TEngine.dir/includes_C.rsp
CMakeFiles/TEngine.dir/src/camera.c.obj: ../src/camera.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Eigene Dateien\Programmieren\C\CLion-Workspace\TEngine\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_9) "Building C object CMakeFiles/TEngine.dir/src/camera.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\TEngine.dir\src\camera.c.obj   -c "C:\Eigene Dateien\Programmieren\C\CLion-Workspace\TEngine\src\camera.c"

CMakeFiles/TEngine.dir/src/camera.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TEngine.dir/src/camera.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:\Eigene Dateien\Programmieren\C\CLion-Workspace\TEngine\src\camera.c" > CMakeFiles\TEngine.dir\src\camera.c.i

CMakeFiles/TEngine.dir/src/camera.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TEngine.dir/src/camera.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "C:\Eigene Dateien\Programmieren\C\CLion-Workspace\TEngine\src\camera.c" -o CMakeFiles\TEngine.dir\src\camera.c.s

CMakeFiles/TEngine.dir/src/mesh.c.obj: CMakeFiles/TEngine.dir/flags.make
CMakeFiles/TEngine.dir/src/mesh.c.obj: CMakeFiles/TEngine.dir/includes_C.rsp
CMakeFiles/TEngine.dir/src/mesh.c.obj: ../src/mesh.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Eigene Dateien\Programmieren\C\CLion-Workspace\TEngine\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_10) "Building C object CMakeFiles/TEngine.dir/src/mesh.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\TEngine.dir\src\mesh.c.obj   -c "C:\Eigene Dateien\Programmieren\C\CLion-Workspace\TEngine\src\mesh.c"

CMakeFiles/TEngine.dir/src/mesh.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TEngine.dir/src/mesh.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:\Eigene Dateien\Programmieren\C\CLion-Workspace\TEngine\src\mesh.c" > CMakeFiles\TEngine.dir\src\mesh.c.i

CMakeFiles/TEngine.dir/src/mesh.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TEngine.dir/src/mesh.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "C:\Eigene Dateien\Programmieren\C\CLion-Workspace\TEngine\src\mesh.c" -o CMakeFiles\TEngine.dir\src\mesh.c.s

CMakeFiles/TEngine.dir/src/light.c.obj: CMakeFiles/TEngine.dir/flags.make
CMakeFiles/TEngine.dir/src/light.c.obj: CMakeFiles/TEngine.dir/includes_C.rsp
CMakeFiles/TEngine.dir/src/light.c.obj: ../src/light.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Eigene Dateien\Programmieren\C\CLion-Workspace\TEngine\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_11) "Building C object CMakeFiles/TEngine.dir/src/light.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\TEngine.dir\src\light.c.obj   -c "C:\Eigene Dateien\Programmieren\C\CLion-Workspace\TEngine\src\light.c"

CMakeFiles/TEngine.dir/src/light.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TEngine.dir/src/light.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:\Eigene Dateien\Programmieren\C\CLion-Workspace\TEngine\src\light.c" > CMakeFiles\TEngine.dir\src\light.c.i

CMakeFiles/TEngine.dir/src/light.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TEngine.dir/src/light.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "C:\Eigene Dateien\Programmieren\C\CLion-Workspace\TEngine\src\light.c" -o CMakeFiles\TEngine.dir\src\light.c.s

CMakeFiles/TEngine.dir/src/filehelper.c.obj: CMakeFiles/TEngine.dir/flags.make
CMakeFiles/TEngine.dir/src/filehelper.c.obj: CMakeFiles/TEngine.dir/includes_C.rsp
CMakeFiles/TEngine.dir/src/filehelper.c.obj: ../src/filehelper.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Eigene Dateien\Programmieren\C\CLion-Workspace\TEngine\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_12) "Building C object CMakeFiles/TEngine.dir/src/filehelper.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\TEngine.dir\src\filehelper.c.obj   -c "C:\Eigene Dateien\Programmieren\C\CLion-Workspace\TEngine\src\filehelper.c"

CMakeFiles/TEngine.dir/src/filehelper.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TEngine.dir/src/filehelper.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:\Eigene Dateien\Programmieren\C\CLion-Workspace\TEngine\src\filehelper.c" > CMakeFiles\TEngine.dir\src\filehelper.c.i

CMakeFiles/TEngine.dir/src/filehelper.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TEngine.dir/src/filehelper.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "C:\Eigene Dateien\Programmieren\C\CLion-Workspace\TEngine\src\filehelper.c" -o CMakeFiles\TEngine.dir\src\filehelper.c.s

CMakeFiles/TEngine.dir/src/tengine_math.c.obj: CMakeFiles/TEngine.dir/flags.make
CMakeFiles/TEngine.dir/src/tengine_math.c.obj: CMakeFiles/TEngine.dir/includes_C.rsp
CMakeFiles/TEngine.dir/src/tengine_math.c.obj: ../src/tengine_math.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Eigene Dateien\Programmieren\C\CLion-Workspace\TEngine\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_13) "Building C object CMakeFiles/TEngine.dir/src/tengine_math.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\TEngine.dir\src\tengine_math.c.obj   -c "C:\Eigene Dateien\Programmieren\C\CLion-Workspace\TEngine\src\tengine_math.c"

CMakeFiles/TEngine.dir/src/tengine_math.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TEngine.dir/src/tengine_math.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:\Eigene Dateien\Programmieren\C\CLion-Workspace\TEngine\src\tengine_math.c" > CMakeFiles\TEngine.dir\src\tengine_math.c.i

CMakeFiles/TEngine.dir/src/tengine_math.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TEngine.dir/src/tengine_math.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "C:\Eigene Dateien\Programmieren\C\CLion-Workspace\TEngine\src\tengine_math.c" -o CMakeFiles\TEngine.dir\src\tengine_math.c.s

CMakeFiles/TEngine.dir/src/vector.c.obj: CMakeFiles/TEngine.dir/flags.make
CMakeFiles/TEngine.dir/src/vector.c.obj: CMakeFiles/TEngine.dir/includes_C.rsp
CMakeFiles/TEngine.dir/src/vector.c.obj: ../src/vector.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Eigene Dateien\Programmieren\C\CLion-Workspace\TEngine\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_14) "Building C object CMakeFiles/TEngine.dir/src/vector.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\TEngine.dir\src\vector.c.obj   -c "C:\Eigene Dateien\Programmieren\C\CLion-Workspace\TEngine\src\vector.c"

CMakeFiles/TEngine.dir/src/vector.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TEngine.dir/src/vector.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:\Eigene Dateien\Programmieren\C\CLion-Workspace\TEngine\src\vector.c" > CMakeFiles\TEngine.dir\src\vector.c.i

CMakeFiles/TEngine.dir/src/vector.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TEngine.dir/src/vector.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "C:\Eigene Dateien\Programmieren\C\CLion-Workspace\TEngine\src\vector.c" -o CMakeFiles\TEngine.dir\src\vector.c.s

CMakeFiles/TEngine.dir/src/framebuffer.c.obj: CMakeFiles/TEngine.dir/flags.make
CMakeFiles/TEngine.dir/src/framebuffer.c.obj: CMakeFiles/TEngine.dir/includes_C.rsp
CMakeFiles/TEngine.dir/src/framebuffer.c.obj: ../src/framebuffer.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Eigene Dateien\Programmieren\C\CLion-Workspace\TEngine\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_15) "Building C object CMakeFiles/TEngine.dir/src/framebuffer.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\TEngine.dir\src\framebuffer.c.obj   -c "C:\Eigene Dateien\Programmieren\C\CLion-Workspace\TEngine\src\framebuffer.c"

CMakeFiles/TEngine.dir/src/framebuffer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TEngine.dir/src/framebuffer.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:\Eigene Dateien\Programmieren\C\CLion-Workspace\TEngine\src\framebuffer.c" > CMakeFiles\TEngine.dir\src\framebuffer.c.i

CMakeFiles/TEngine.dir/src/framebuffer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TEngine.dir/src/framebuffer.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "C:\Eigene Dateien\Programmieren\C\CLion-Workspace\TEngine\src\framebuffer.c" -o CMakeFiles\TEngine.dir\src\framebuffer.c.s

# Object files for target TEngine
TEngine_OBJECTS = \
"CMakeFiles/TEngine.dir/src/main.c.obj" \
"CMakeFiles/TEngine.dir/src/model.c.obj" \
"CMakeFiles/TEngine.dir/src/texture.c.obj" \
"CMakeFiles/TEngine.dir/src/render.c.obj" \
"CMakeFiles/TEngine.dir/src/lodepng.c.obj" \
"CMakeFiles/TEngine.dir/src/display.c.obj" \
"CMakeFiles/TEngine.dir/src/utils.c.obj" \
"CMakeFiles/TEngine.dir/src/program.c.obj" \
"CMakeFiles/TEngine.dir/src/camera.c.obj" \
"CMakeFiles/TEngine.dir/src/mesh.c.obj" \
"CMakeFiles/TEngine.dir/src/light.c.obj" \
"CMakeFiles/TEngine.dir/src/filehelper.c.obj" \
"CMakeFiles/TEngine.dir/src/tengine_math.c.obj" \
"CMakeFiles/TEngine.dir/src/vector.c.obj" \
"CMakeFiles/TEngine.dir/src/framebuffer.c.obj"

# External object files for target TEngine
TEngine_EXTERNAL_OBJECTS =

TEngine.exe: CMakeFiles/TEngine.dir/src/main.c.obj
TEngine.exe: CMakeFiles/TEngine.dir/src/model.c.obj
TEngine.exe: CMakeFiles/TEngine.dir/src/texture.c.obj
TEngine.exe: CMakeFiles/TEngine.dir/src/render.c.obj
TEngine.exe: CMakeFiles/TEngine.dir/src/lodepng.c.obj
TEngine.exe: CMakeFiles/TEngine.dir/src/display.c.obj
TEngine.exe: CMakeFiles/TEngine.dir/src/utils.c.obj
TEngine.exe: CMakeFiles/TEngine.dir/src/program.c.obj
TEngine.exe: CMakeFiles/TEngine.dir/src/camera.c.obj
TEngine.exe: CMakeFiles/TEngine.dir/src/mesh.c.obj
TEngine.exe: CMakeFiles/TEngine.dir/src/light.c.obj
TEngine.exe: CMakeFiles/TEngine.dir/src/filehelper.c.obj
TEngine.exe: CMakeFiles/TEngine.dir/src/tengine_math.c.obj
TEngine.exe: CMakeFiles/TEngine.dir/src/vector.c.obj
TEngine.exe: CMakeFiles/TEngine.dir/src/framebuffer.c.obj
TEngine.exe: CMakeFiles/TEngine.dir/build.make
TEngine.exe: C:/MinGW/lib/libopengl32.a
TEngine.exe: ../dependencies/glew/lib/libGLEW_2.dll.a
TEngine.exe: ../dependencies/sdl2/lib/libSDL2main.a
TEngine.exe: ../dependencies/sdl2/lib/libSDL2.dll.a
TEngine.exe: CMakeFiles/TEngine.dir/linklibs.rsp
TEngine.exe: CMakeFiles/TEngine.dir/objects1.rsp
TEngine.exe: CMakeFiles/TEngine.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Eigene Dateien\Programmieren\C\CLion-Workspace\TEngine\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_16) "Linking C executable TEngine.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\TEngine.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TEngine.dir/build: TEngine.exe

.PHONY : CMakeFiles/TEngine.dir/build

CMakeFiles/TEngine.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\TEngine.dir\cmake_clean.cmake
.PHONY : CMakeFiles/TEngine.dir/clean

CMakeFiles/TEngine.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Eigene Dateien\Programmieren\C\CLion-Workspace\TEngine" "C:\Eigene Dateien\Programmieren\C\CLion-Workspace\TEngine" "C:\Eigene Dateien\Programmieren\C\CLion-Workspace\TEngine\cmake-build-debug" "C:\Eigene Dateien\Programmieren\C\CLion-Workspace\TEngine\cmake-build-debug" "C:\Eigene Dateien\Programmieren\C\CLion-Workspace\TEngine\cmake-build-debug\CMakeFiles\TEngine.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/TEngine.dir/depend

