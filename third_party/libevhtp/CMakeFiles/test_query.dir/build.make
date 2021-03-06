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
include CMakeFiles/test_query.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/test_query.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test_query.dir/flags.make

CMakeFiles/test_query.dir/examples/test_query.c.o: CMakeFiles/test_query.dir/flags.make
CMakeFiles/test_query.dir/examples/test_query.c.o: examples/test_query.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mpr/projects/mpr_pay_gateway/third_party/libevhtp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/test_query.dir/examples/test_query.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/test_query.dir/examples/test_query.c.o   -c /home/mpr/projects/mpr_pay_gateway/third_party/libevhtp/examples/test_query.c

CMakeFiles/test_query.dir/examples/test_query.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/test_query.dir/examples/test_query.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/mpr/projects/mpr_pay_gateway/third_party/libevhtp/examples/test_query.c > CMakeFiles/test_query.dir/examples/test_query.c.i

CMakeFiles/test_query.dir/examples/test_query.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/test_query.dir/examples/test_query.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/mpr/projects/mpr_pay_gateway/third_party/libevhtp/examples/test_query.c -o CMakeFiles/test_query.dir/examples/test_query.c.s

CMakeFiles/test_query.dir/examples/test_query.c.o.requires:

.PHONY : CMakeFiles/test_query.dir/examples/test_query.c.o.requires

CMakeFiles/test_query.dir/examples/test_query.c.o.provides: CMakeFiles/test_query.dir/examples/test_query.c.o.requires
	$(MAKE) -f CMakeFiles/test_query.dir/build.make CMakeFiles/test_query.dir/examples/test_query.c.o.provides.build
.PHONY : CMakeFiles/test_query.dir/examples/test_query.c.o.provides

CMakeFiles/test_query.dir/examples/test_query.c.o.provides.build: CMakeFiles/test_query.dir/examples/test_query.c.o


# Object files for target test_query
test_query_OBJECTS = \
"CMakeFiles/test_query.dir/examples/test_query.c.o"

# External object files for target test_query
test_query_EXTERNAL_OBJECTS =

test_query: CMakeFiles/test_query.dir/examples/test_query.c.o
test_query: CMakeFiles/test_query.dir/build.make
test_query: libevhtp.a
test_query: /usr/local/lib/libevent.so
test_query: /usr/lib/x86_64-linux-gnu/libevent_pthreads.so
test_query: /usr/lib/x86_64-linux-gnu/libevent_openssl.so
test_query: /usr/lib/x86_64-linux-gnu/libssl.so
test_query: /usr/lib/x86_64-linux-gnu/libcrypto.so
test_query: /usr/lib/x86_64-linux-gnu/libdl.so
test_query: /usr/lib/x86_64-linux-gnu/librt.so
test_query: CMakeFiles/test_query.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mpr/projects/mpr_pay_gateway/third_party/libevhtp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable test_query"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_query.dir/link.txt --verbose=$(VERBOSE)
	/usr/bin/objcopy --only-keep-debug /home/mpr/projects/mpr_pay_gateway/third_party/libevhtp/test_query /home/mpr/projects/mpr_pay_gateway/third_party/libevhtp/test_query.debug
	/usr/bin/objcopy --strip-all --strip-unneeded /home/mpr/projects/mpr_pay_gateway/third_party/libevhtp/test_query
	/usr/bin/objcopy --add-gnu-debuglink=test_query.debug /home/mpr/projects/mpr_pay_gateway/third_party/libevhtp/test_query
	/usr/local/bin/cmake -E copy_if_different /home/mpr/projects/mpr_pay_gateway/third_party/libevhtp/test_query /home/mpr/projects/mpr_pay_gateway/third_party/libevhtp/install/bin

# Rule to build all files generated by this target.
CMakeFiles/test_query.dir/build: test_query

.PHONY : CMakeFiles/test_query.dir/build

CMakeFiles/test_query.dir/requires: CMakeFiles/test_query.dir/examples/test_query.c.o.requires

.PHONY : CMakeFiles/test_query.dir/requires

CMakeFiles/test_query.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test_query.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test_query.dir/clean

CMakeFiles/test_query.dir/depend:
	cd /home/mpr/projects/mpr_pay_gateway/third_party/libevhtp && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mpr/projects/mpr_pay_gateway/third_party/libevhtp /home/mpr/projects/mpr_pay_gateway/third_party/libevhtp /home/mpr/projects/mpr_pay_gateway/third_party/libevhtp /home/mpr/projects/mpr_pay_gateway/third_party/libevhtp /home/mpr/projects/mpr_pay_gateway/third_party/libevhtp/CMakeFiles/test_query.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test_query.dir/depend

