# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake.exe

# The command to remove a file.
RM = /usr/bin/cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/cygdrive/c/MAGDISS3D/THE NEWEST VERSION"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/cygdrive/c/MAGDISS3D/THE NEWEST VERSION/src"

# Utility rule file for ContinuousSubmit.

# Include any custom commands dependencies for this target.
include contrib/yaml-cpp/CMakeFiles/ContinuousSubmit.dir/compiler_depend.make

# Include the progress variables for this target.
include contrib/yaml-cpp/CMakeFiles/ContinuousSubmit.dir/progress.make

contrib/yaml-cpp/CMakeFiles/ContinuousSubmit:
	cd "/cygdrive/c/MAGDISS3D/THE NEWEST VERSION/src/contrib/yaml-cpp" && /usr/bin/ctest.exe -D ContinuousSubmit

ContinuousSubmit: contrib/yaml-cpp/CMakeFiles/ContinuousSubmit
ContinuousSubmit: contrib/yaml-cpp/CMakeFiles/ContinuousSubmit.dir/build.make
.PHONY : ContinuousSubmit

# Rule to build all files generated by this target.
contrib/yaml-cpp/CMakeFiles/ContinuousSubmit.dir/build: ContinuousSubmit
.PHONY : contrib/yaml-cpp/CMakeFiles/ContinuousSubmit.dir/build

contrib/yaml-cpp/CMakeFiles/ContinuousSubmit.dir/clean:
	cd "/cygdrive/c/MAGDISS3D/THE NEWEST VERSION/src/contrib/yaml-cpp" && $(CMAKE_COMMAND) -P CMakeFiles/ContinuousSubmit.dir/cmake_clean.cmake
.PHONY : contrib/yaml-cpp/CMakeFiles/ContinuousSubmit.dir/clean

contrib/yaml-cpp/CMakeFiles/ContinuousSubmit.dir/depend:
	cd "/cygdrive/c/MAGDISS3D/THE NEWEST VERSION/src" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/cygdrive/c/MAGDISS3D/THE NEWEST VERSION" "/cygdrive/c/MAGDISS3D/THE NEWEST VERSION/contrib/yaml-cpp" "/cygdrive/c/MAGDISS3D/THE NEWEST VERSION/src" "/cygdrive/c/MAGDISS3D/THE NEWEST VERSION/src/contrib/yaml-cpp" "/cygdrive/c/MAGDISS3D/THE NEWEST VERSION/src/contrib/yaml-cpp/CMakeFiles/ContinuousSubmit.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : contrib/yaml-cpp/CMakeFiles/ContinuousSubmit.dir/depend
