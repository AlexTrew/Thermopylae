# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/alex/Downloads/clion-2020.2.1/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/alex/Downloads/clion-2020.2.1/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/alex/CLionProjects/Thermopylae

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/alex/CLionProjects/Thermopylae/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/ncurses.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ncurses.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ncurses.dir/flags.make

CMakeFiles/ncurses.dir/main.cpp.o: CMakeFiles/ncurses.dir/flags.make
CMakeFiles/ncurses.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alex/CLionProjects/Thermopylae/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ncurses.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ncurses.dir/main.cpp.o -c /home/alex/CLionProjects/Thermopylae/main.cpp

CMakeFiles/ncurses.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ncurses.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alex/CLionProjects/Thermopylae/main.cpp > CMakeFiles/ncurses.dir/main.cpp.i

CMakeFiles/ncurses.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ncurses.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alex/CLionProjects/Thermopylae/main.cpp -o CMakeFiles/ncurses.dir/main.cpp.s

# Object files for target ncurses
ncurses_OBJECTS = \
"CMakeFiles/ncurses.dir/main.cpp.o"

# External object files for target ncurses
ncurses_EXTERNAL_OBJECTS =

libncurses.a: CMakeFiles/ncurses.dir/main.cpp.o
libncurses.a: CMakeFiles/ncurses.dir/build.make
libncurses.a: CMakeFiles/ncurses.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/alex/CLionProjects/Thermopylae/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libncurses.a"
	$(CMAKE_COMMAND) -P CMakeFiles/ncurses.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ncurses.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ncurses.dir/build: libncurses.a

.PHONY : CMakeFiles/ncurses.dir/build

CMakeFiles/ncurses.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ncurses.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ncurses.dir/clean

CMakeFiles/ncurses.dir/depend:
	cd /home/alex/CLionProjects/Thermopylae/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alex/CLionProjects/Thermopylae /home/alex/CLionProjects/Thermopylae /home/alex/CLionProjects/Thermopylae/cmake-build-debug /home/alex/CLionProjects/Thermopylae/cmake-build-debug /home/alex/CLionProjects/Thermopylae/cmake-build-debug/CMakeFiles/ncurses.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ncurses.dir/depend

