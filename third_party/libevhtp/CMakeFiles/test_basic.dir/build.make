# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.4

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/mpr/projects/mpr_pay_gateway/third_party/libevhtp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mpr/projects/mpr_pay_gateway/third_party/libevhtp

# Include any dependencies generated for this target.
include CMakeFiles/test_basic.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/test_basic.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test_basic.dir/flags.make

CMakeFiles/test_basic.dir/examples/test_basic.c.o: CMakeFiles/test_basic.dir/flags.make
CMakeFiles/test_basic.dir/examples/test_basic.c.o: examples/test_basic.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mpr/projects/mpr_pay_gateway/third_party/libevhtp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/test_basic.dir/examples/test_basic.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/test_basic.dir/examples/test_basic.c.o   -c /home/mpr/projects/mpr_pay_gateway/third_party/libevhtp/examples/test_basic.c

CMakeFiles/test_basic.dir/examples/test_basic.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/test_basic.dir/examples/test_basic.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/mpr/projects/mpr_pay_gateway/third_party/libevhtp/examples/test_basic.c > CMakeFiles/test_basic.dir/examples/test_basic.c.i

CMakeFiles/test_basic.dir/examples/test_basic.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/test_basic.dir/examples/test_basic.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/mpr/projects/mpr_pay_gateway/third_party/libevhtp/examples/test_basic.c -o CMakeFiles/test_basic.dir/examples/test_basic.c.s

CMakeFiles/test_basic.dir/examples/test_basic.c.o.requires:

.PHONY : CMakeFiles/test_basic.dir/examples/test_basic.c.o.requires

CMakeFiles/test_basic.dir/examples/test_basic.c.o.provides: CMakeFiles/test_basic.dir/examples/test_basic.c.o.requires
	$(MAKE) -f CMakeFiles/test_basic.dir/build.make CMakeFiles/test_basic.dir/examples/test_basic.c.o.provides.build
.PHONY : CMakeFiles/test_basic.dir/examples/test_basic.c.o.provides

CMakeFiles/test_basic.dir/examples/test_basic.c.o.provides.build: CMakeFiles/test_basic.dir/examples/test_basic.c.o


# Object files for target test_basic
test_basic_OBJECTS = \
"CMakeFiles/test_basic.dir/examples/test_basic.c.o"

# External object files for target test_basic
test_basic_EXTERNAL_OBJECTS =

test_basic: CMakeFiles/test_basic.dir/examples/test_basic.c.o
test_basic: CMakeFiles/test_basic.dir/build.make
test_basic: libevhtp.a
test_basic: /usr/local/lib/libevent.so
test_basic: /usr/lib/x86_64-linux-gnu/libevent_pthreads.so
test_basic: /usr/lib/x86_64-linux-gnu/libevent_openssl.so
test_basic: /usr/lib/x86_64-linux-gnu/libssl.so
test_basic: /usr/lib/x86_64-linux-gnu/libcrypto.so
test_basic: /usr/lib/x86_64-linux-gnu/libdl.so
test_basic: /usr/lib/x86_64-linux-gnu/librt.so
test_basic: CMakeFiles/test_basic.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mpr/projects/mpr_pay_gateway/third_party/libevhtp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable test_basic"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_basic.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test_basic.dir/build: test_basic

.PHONY : CMakeFiles/test_basic.dir/build

CMakeFiles/test_basic.dir/requires: CMakeFiles/test_basic.dir/examples/test_basic.c.o.requires

.PHONY : CMakeFiles/test_basic.dir/requires

CMakeFiles/test_basic.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test_basic.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test_basic.dir/clean

CMakeFiles/test_basic.dir/depend:
	cd /home/mpr/projects/mpr_pay_gateway/third_party/libevhtp && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mpr/projects/mpr_pay_gateway/third_party/libevhtp /home/mpr/projects/mpr_pay_gateway/third_party/libevhtp /home/mpr/projects/mpr_pay_gateway/third_party/libevhtp /home/mpr/projects/mpr_pay_gateway/third_party/libevhtp /home/mpr/projects/mpr_pay_gateway/third_party/libevhtp/CMakeFiles/test_basic.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test_basic.dir/depend

