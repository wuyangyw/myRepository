# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

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
CMAKE_COMMAND = /home/yw/compiler/cmake/bin/cmake

# The command to remove a file.
RM = /home/yw/compiler/cmake/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/yw/demo/demo3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yw/demo/demo3/build

# Include any dependencies generated for this target.
include CMakeFiles/mian_cmake.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/mian_cmake.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/mian_cmake.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mian_cmake.dir/flags.make

CMakeFiles/mian_cmake.dir/main.cpp.o: CMakeFiles/mian_cmake.dir/flags.make
CMakeFiles/mian_cmake.dir/main.cpp.o: ../main.cpp
CMakeFiles/mian_cmake.dir/main.cpp.o: CMakeFiles/mian_cmake.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yw/demo/demo3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/mian_cmake.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/mian_cmake.dir/main.cpp.o -MF CMakeFiles/mian_cmake.dir/main.cpp.o.d -o CMakeFiles/mian_cmake.dir/main.cpp.o -c /home/yw/demo/demo3/main.cpp

CMakeFiles/mian_cmake.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mian_cmake.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yw/demo/demo3/main.cpp > CMakeFiles/mian_cmake.dir/main.cpp.i

CMakeFiles/mian_cmake.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mian_cmake.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yw/demo/demo3/main.cpp -o CMakeFiles/mian_cmake.dir/main.cpp.s

CMakeFiles/mian_cmake.dir/src/Soldier.cpp.o: CMakeFiles/mian_cmake.dir/flags.make
CMakeFiles/mian_cmake.dir/src/Soldier.cpp.o: ../src/Soldier.cpp
CMakeFiles/mian_cmake.dir/src/Soldier.cpp.o: CMakeFiles/mian_cmake.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yw/demo/demo3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/mian_cmake.dir/src/Soldier.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/mian_cmake.dir/src/Soldier.cpp.o -MF CMakeFiles/mian_cmake.dir/src/Soldier.cpp.o.d -o CMakeFiles/mian_cmake.dir/src/Soldier.cpp.o -c /home/yw/demo/demo3/src/Soldier.cpp

CMakeFiles/mian_cmake.dir/src/Soldier.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mian_cmake.dir/src/Soldier.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yw/demo/demo3/src/Soldier.cpp > CMakeFiles/mian_cmake.dir/src/Soldier.cpp.i

CMakeFiles/mian_cmake.dir/src/Soldier.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mian_cmake.dir/src/Soldier.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yw/demo/demo3/src/Soldier.cpp -o CMakeFiles/mian_cmake.dir/src/Soldier.cpp.s

CMakeFiles/mian_cmake.dir/src/Gun.cpp.o: CMakeFiles/mian_cmake.dir/flags.make
CMakeFiles/mian_cmake.dir/src/Gun.cpp.o: ../src/Gun.cpp
CMakeFiles/mian_cmake.dir/src/Gun.cpp.o: CMakeFiles/mian_cmake.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yw/demo/demo3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/mian_cmake.dir/src/Gun.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/mian_cmake.dir/src/Gun.cpp.o -MF CMakeFiles/mian_cmake.dir/src/Gun.cpp.o.d -o CMakeFiles/mian_cmake.dir/src/Gun.cpp.o -c /home/yw/demo/demo3/src/Gun.cpp

CMakeFiles/mian_cmake.dir/src/Gun.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mian_cmake.dir/src/Gun.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yw/demo/demo3/src/Gun.cpp > CMakeFiles/mian_cmake.dir/src/Gun.cpp.i

CMakeFiles/mian_cmake.dir/src/Gun.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mian_cmake.dir/src/Gun.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yw/demo/demo3/src/Gun.cpp -o CMakeFiles/mian_cmake.dir/src/Gun.cpp.s

# Object files for target mian_cmake
mian_cmake_OBJECTS = \
"CMakeFiles/mian_cmake.dir/main.cpp.o" \
"CMakeFiles/mian_cmake.dir/src/Soldier.cpp.o" \
"CMakeFiles/mian_cmake.dir/src/Gun.cpp.o"

# External object files for target mian_cmake
mian_cmake_EXTERNAL_OBJECTS =

mian_cmake: CMakeFiles/mian_cmake.dir/main.cpp.o
mian_cmake: CMakeFiles/mian_cmake.dir/src/Soldier.cpp.o
mian_cmake: CMakeFiles/mian_cmake.dir/src/Gun.cpp.o
mian_cmake: CMakeFiles/mian_cmake.dir/build.make
mian_cmake: CMakeFiles/mian_cmake.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/yw/demo/demo3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable mian_cmake"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mian_cmake.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mian_cmake.dir/build: mian_cmake
.PHONY : CMakeFiles/mian_cmake.dir/build

CMakeFiles/mian_cmake.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mian_cmake.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mian_cmake.dir/clean

CMakeFiles/mian_cmake.dir/depend:
	cd /home/yw/demo/demo3/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yw/demo/demo3 /home/yw/demo/demo3 /home/yw/demo/demo3/build /home/yw/demo/demo3/build /home/yw/demo/demo3/build/CMakeFiles/mian_cmake.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mian_cmake.dir/depend
