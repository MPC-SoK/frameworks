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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.17.2/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.17.2/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/wangxiao/git/frameworks/emp/sh_test

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/wangxiao/git/frameworks/emp/sh_test

# Include any dependencies generated for this target.
include CMakeFiles/xtabs.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/xtabs.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/xtabs.dir/flags.make

CMakeFiles/xtabs.dir/test/xtabs.cpp.o: CMakeFiles/xtabs.dir/flags.make
CMakeFiles/xtabs.dir/test/xtabs.cpp.o: test/xtabs.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/wangxiao/git/frameworks/emp/sh_test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/xtabs.dir/test/xtabs.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/xtabs.dir/test/xtabs.cpp.o -c /Users/wangxiao/git/frameworks/emp/sh_test/test/xtabs.cpp

CMakeFiles/xtabs.dir/test/xtabs.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/xtabs.dir/test/xtabs.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/wangxiao/git/frameworks/emp/sh_test/test/xtabs.cpp > CMakeFiles/xtabs.dir/test/xtabs.cpp.i

CMakeFiles/xtabs.dir/test/xtabs.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/xtabs.dir/test/xtabs.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/wangxiao/git/frameworks/emp/sh_test/test/xtabs.cpp -o CMakeFiles/xtabs.dir/test/xtabs.cpp.s

# Object files for target xtabs
xtabs_OBJECTS = \
"CMakeFiles/xtabs.dir/test/xtabs.cpp.o"

# External object files for target xtabs
xtabs_EXTERNAL_OBJECTS =

bin/xtabs: CMakeFiles/xtabs.dir/test/xtabs.cpp.o
bin/xtabs: CMakeFiles/xtabs.dir/build.make
bin/xtabs: /usr/local/opt/openssl/lib/libssl.dylib
bin/xtabs: /usr/local/opt/openssl/lib/libcrypto.dylib
bin/xtabs: /usr/local/lib/libemp-tool.dylib
bin/xtabs: CMakeFiles/xtabs.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/wangxiao/git/frameworks/emp/sh_test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bin/xtabs"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/xtabs.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/xtabs.dir/build: bin/xtabs

.PHONY : CMakeFiles/xtabs.dir/build

CMakeFiles/xtabs.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/xtabs.dir/cmake_clean.cmake
.PHONY : CMakeFiles/xtabs.dir/clean

CMakeFiles/xtabs.dir/depend:
	cd /Users/wangxiao/git/frameworks/emp/sh_test && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/wangxiao/git/frameworks/emp/sh_test /Users/wangxiao/git/frameworks/emp/sh_test /Users/wangxiao/git/frameworks/emp/sh_test /Users/wangxiao/git/frameworks/emp/sh_test /Users/wangxiao/git/frameworks/emp/sh_test/CMakeFiles/xtabs.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/xtabs.dir/depend
