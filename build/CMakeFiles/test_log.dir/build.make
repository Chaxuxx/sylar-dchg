# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/c/Users/DchG/Desktop/myserver/sylar-dchg

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/DchG/Desktop/myserver/sylar-dchg/build

# Include any dependencies generated for this target.
include CMakeFiles/test_log.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/test_log.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test_log.dir/flags.make

CMakeFiles/test_log.dir/tests/test.cc.o: CMakeFiles/test_log.dir/flags.make
CMakeFiles/test_log.dir/tests/test.cc.o: ../tests/test.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/DchG/Desktop/myserver/sylar-dchg/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test_log.dir/tests/test.cc.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_log.dir/tests/test.cc.o -c /mnt/c/Users/DchG/Desktop/myserver/sylar-dchg/tests/test.cc

CMakeFiles/test_log.dir/tests/test.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_log.dir/tests/test.cc.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/DchG/Desktop/myserver/sylar-dchg/tests/test.cc > CMakeFiles/test_log.dir/tests/test.cc.i

CMakeFiles/test_log.dir/tests/test.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_log.dir/tests/test.cc.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/DchG/Desktop/myserver/sylar-dchg/tests/test.cc -o CMakeFiles/test_log.dir/tests/test.cc.s

# Object files for target test_log
test_log_OBJECTS = \
"CMakeFiles/test_log.dir/tests/test.cc.o"

# External object files for target test_log
test_log_EXTERNAL_OBJECTS =

test_log: CMakeFiles/test_log.dir/tests/test.cc.o
test_log: CMakeFiles/test_log.dir/build.make
test_log: libsylar_dchg.so
test_log: CMakeFiles/test_log.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/DchG/Desktop/myserver/sylar-dchg/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test_log"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_log.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test_log.dir/build: test_log

.PHONY : CMakeFiles/test_log.dir/build

CMakeFiles/test_log.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test_log.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test_log.dir/clean

CMakeFiles/test_log.dir/depend:
	cd /mnt/c/Users/DchG/Desktop/myserver/sylar-dchg/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/DchG/Desktop/myserver/sylar-dchg /mnt/c/Users/DchG/Desktop/myserver/sylar-dchg /mnt/c/Users/DchG/Desktop/myserver/sylar-dchg/build /mnt/c/Users/DchG/Desktop/myserver/sylar-dchg/build /mnt/c/Users/DchG/Desktop/myserver/sylar-dchg/build/CMakeFiles/test_log.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test_log.dir/depend

