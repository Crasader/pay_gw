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
include CMakeFiles/evhtp.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/evhtp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/evhtp.dir/flags.make

CMakeFiles/evhtp.dir/evhtp.c.o: CMakeFiles/evhtp.dir/flags.make
CMakeFiles/evhtp.dir/evhtp.c.o: evhtp.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mpr/projects/mpr_pay_gateway/third_party/libevhtp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/evhtp.dir/evhtp.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/evhtp.dir/evhtp.c.o   -c /home/mpr/projects/mpr_pay_gateway/third_party/libevhtp/evhtp.c

CMakeFiles/evhtp.dir/evhtp.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/evhtp.dir/evhtp.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/mpr/projects/mpr_pay_gateway/third_party/libevhtp/evhtp.c > CMakeFiles/evhtp.dir/evhtp.c.i

CMakeFiles/evhtp.dir/evhtp.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/evhtp.dir/evhtp.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/mpr/projects/mpr_pay_gateway/third_party/libevhtp/evhtp.c -o CMakeFiles/evhtp.dir/evhtp.c.s

CMakeFiles/evhtp.dir/evhtp.c.o.requires:

.PHONY : CMakeFiles/evhtp.dir/evhtp.c.o.requires

CMakeFiles/evhtp.dir/evhtp.c.o.provides: CMakeFiles/evhtp.dir/evhtp.c.o.requires
	$(MAKE) -f CMakeFiles/evhtp.dir/build.make CMakeFiles/evhtp.dir/evhtp.c.o.provides.build
.PHONY : CMakeFiles/evhtp.dir/evhtp.c.o.provides

CMakeFiles/evhtp.dir/evhtp.c.o.provides.build: CMakeFiles/evhtp.dir/evhtp.c.o


CMakeFiles/evhtp.dir/evhtp_numtoa.c.o: CMakeFiles/evhtp.dir/flags.make
CMakeFiles/evhtp.dir/evhtp_numtoa.c.o: evhtp_numtoa.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mpr/projects/mpr_pay_gateway/third_party/libevhtp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/evhtp.dir/evhtp_numtoa.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/evhtp.dir/evhtp_numtoa.c.o   -c /home/mpr/projects/mpr_pay_gateway/third_party/libevhtp/evhtp_numtoa.c

CMakeFiles/evhtp.dir/evhtp_numtoa.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/evhtp.dir/evhtp_numtoa.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/mpr/projects/mpr_pay_gateway/third_party/libevhtp/evhtp_numtoa.c > CMakeFiles/evhtp.dir/evhtp_numtoa.c.i

CMakeFiles/evhtp.dir/evhtp_numtoa.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/evhtp.dir/evhtp_numtoa.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/mpr/projects/mpr_pay_gateway/third_party/libevhtp/evhtp_numtoa.c -o CMakeFiles/evhtp.dir/evhtp_numtoa.c.s

CMakeFiles/evhtp.dir/evhtp_numtoa.c.o.requires:

.PHONY : CMakeFiles/evhtp.dir/evhtp_numtoa.c.o.requires

CMakeFiles/evhtp.dir/evhtp_numtoa.c.o.provides: CMakeFiles/evhtp.dir/evhtp_numtoa.c.o.requires
	$(MAKE) -f CMakeFiles/evhtp.dir/build.make CMakeFiles/evhtp.dir/evhtp_numtoa.c.o.provides.build
.PHONY : CMakeFiles/evhtp.dir/evhtp_numtoa.c.o.provides

CMakeFiles/evhtp.dir/evhtp_numtoa.c.o.provides.build: CMakeFiles/evhtp.dir/evhtp_numtoa.c.o


CMakeFiles/evhtp.dir/htparse/htparse.c.o: CMakeFiles/evhtp.dir/flags.make
CMakeFiles/evhtp.dir/htparse/htparse.c.o: htparse/htparse.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mpr/projects/mpr_pay_gateway/third_party/libevhtp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/evhtp.dir/htparse/htparse.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/evhtp.dir/htparse/htparse.c.o   -c /home/mpr/projects/mpr_pay_gateway/third_party/libevhtp/htparse/htparse.c

CMakeFiles/evhtp.dir/htparse/htparse.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/evhtp.dir/htparse/htparse.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/mpr/projects/mpr_pay_gateway/third_party/libevhtp/htparse/htparse.c > CMakeFiles/evhtp.dir/htparse/htparse.c.i

CMakeFiles/evhtp.dir/htparse/htparse.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/evhtp.dir/htparse/htparse.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/mpr/projects/mpr_pay_gateway/third_party/libevhtp/htparse/htparse.c -o CMakeFiles/evhtp.dir/htparse/htparse.c.s

CMakeFiles/evhtp.dir/htparse/htparse.c.o.requires:

.PHONY : CMakeFiles/evhtp.dir/htparse/htparse.c.o.requires

CMakeFiles/evhtp.dir/htparse/htparse.c.o.provides: CMakeFiles/evhtp.dir/htparse/htparse.c.o.requires
	$(MAKE) -f CMakeFiles/evhtp.dir/build.make CMakeFiles/evhtp.dir/htparse/htparse.c.o.provides.build
.PHONY : CMakeFiles/evhtp.dir/htparse/htparse.c.o.provides

CMakeFiles/evhtp.dir/htparse/htparse.c.o.provides.build: CMakeFiles/evhtp.dir/htparse/htparse.c.o


CMakeFiles/evhtp.dir/evthr/evthr.c.o: CMakeFiles/evhtp.dir/flags.make
CMakeFiles/evhtp.dir/evthr/evthr.c.o: evthr/evthr.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mpr/projects/mpr_pay_gateway/third_party/libevhtp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/evhtp.dir/evthr/evthr.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/evhtp.dir/evthr/evthr.c.o   -c /home/mpr/projects/mpr_pay_gateway/third_party/libevhtp/evthr/evthr.c

CMakeFiles/evhtp.dir/evthr/evthr.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/evhtp.dir/evthr/evthr.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/mpr/projects/mpr_pay_gateway/third_party/libevhtp/evthr/evthr.c > CMakeFiles/evhtp.dir/evthr/evthr.c.i

CMakeFiles/evhtp.dir/evthr/evthr.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/evhtp.dir/evthr/evthr.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/mpr/projects/mpr_pay_gateway/third_party/libevhtp/evthr/evthr.c -o CMakeFiles/evhtp.dir/evthr/evthr.c.s

CMakeFiles/evhtp.dir/evthr/evthr.c.o.requires:

.PHONY : CMakeFiles/evhtp.dir/evthr/evthr.c.o.requires

CMakeFiles/evhtp.dir/evthr/evthr.c.o.provides: CMakeFiles/evhtp.dir/evthr/evthr.c.o.requires
	$(MAKE) -f CMakeFiles/evhtp.dir/build.make CMakeFiles/evhtp.dir/evthr/evthr.c.o.provides.build
.PHONY : CMakeFiles/evhtp.dir/evthr/evthr.c.o.provides

CMakeFiles/evhtp.dir/evthr/evthr.c.o.provides.build: CMakeFiles/evhtp.dir/evthr/evthr.c.o


# Object files for target evhtp
evhtp_OBJECTS = \
"CMakeFiles/evhtp.dir/evhtp.c.o" \
"CMakeFiles/evhtp.dir/evhtp_numtoa.c.o" \
"CMakeFiles/evhtp.dir/htparse/htparse.c.o" \
"CMakeFiles/evhtp.dir/evthr/evthr.c.o"

# External object files for target evhtp
evhtp_EXTERNAL_OBJECTS =

libevhtp.a: CMakeFiles/evhtp.dir/evhtp.c.o
libevhtp.a: CMakeFiles/evhtp.dir/evhtp_numtoa.c.o
libevhtp.a: CMakeFiles/evhtp.dir/htparse/htparse.c.o
libevhtp.a: CMakeFiles/evhtp.dir/evthr/evthr.c.o
libevhtp.a: CMakeFiles/evhtp.dir/build.make
libevhtp.a: CMakeFiles/evhtp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mpr/projects/mpr_pay_gateway/third_party/libevhtp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking C static library libevhtp.a"
	$(CMAKE_COMMAND) -P CMakeFiles/evhtp.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/evhtp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/evhtp.dir/build: libevhtp.a

.PHONY : CMakeFiles/evhtp.dir/build

CMakeFiles/evhtp.dir/requires: CMakeFiles/evhtp.dir/evhtp.c.o.requires
CMakeFiles/evhtp.dir/requires: CMakeFiles/evhtp.dir/evhtp_numtoa.c.o.requires
CMakeFiles/evhtp.dir/requires: CMakeFiles/evhtp.dir/htparse/htparse.c.o.requires
CMakeFiles/evhtp.dir/requires: CMakeFiles/evhtp.dir/evthr/evthr.c.o.requires

.PHONY : CMakeFiles/evhtp.dir/requires

CMakeFiles/evhtp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/evhtp.dir/cmake_clean.cmake
.PHONY : CMakeFiles/evhtp.dir/clean

CMakeFiles/evhtp.dir/depend:
	cd /home/mpr/projects/mpr_pay_gateway/third_party/libevhtp && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mpr/projects/mpr_pay_gateway/third_party/libevhtp /home/mpr/projects/mpr_pay_gateway/third_party/libevhtp /home/mpr/projects/mpr_pay_gateway/third_party/libevhtp /home/mpr/projects/mpr_pay_gateway/third_party/libevhtp /home/mpr/projects/mpr_pay_gateway/third_party/libevhtp/CMakeFiles/evhtp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/evhtp.dir/depend

