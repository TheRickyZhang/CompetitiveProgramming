# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.31

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\Users\ricky\AppData\Local\Programs\CLion\bin\cmake\win\x64\bin\cmake.exe

# The command to remove a file.
RM = C:\Users\ricky\AppData\Local\Programs\CLion\bin\cmake\win\x64\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\ricky\CompetitiveProgramming

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\ricky\CompetitiveProgramming\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/MaximumSumMatchingNodes.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/MaximumSumMatchingNodes.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/MaximumSumMatchingNodes.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MaximumSumMatchingNodes.dir/flags.make

CMakeFiles/MaximumSumMatchingNodes.dir/codegen:
.PHONY : CMakeFiles/MaximumSumMatchingNodes.dir/codegen

CMakeFiles/MaximumSumMatchingNodes.dir/Tester/MaximumSumMatchingNodes.cpp.obj: CMakeFiles/MaximumSumMatchingNodes.dir/flags.make
CMakeFiles/MaximumSumMatchingNodes.dir/Tester/MaximumSumMatchingNodes.cpp.obj: C:/Users/ricky/CompetitiveProgramming/Tester/MaximumSumMatchingNodes.cpp
CMakeFiles/MaximumSumMatchingNodes.dir/Tester/MaximumSumMatchingNodes.cpp.obj: CMakeFiles/MaximumSumMatchingNodes.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\ricky\CompetitiveProgramming\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/MaximumSumMatchingNodes.dir/Tester/MaximumSumMatchingNodes.cpp.obj"
	C:\Users\ricky\AppData\Local\Programs\CLion\bin\mingw\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MaximumSumMatchingNodes.dir/Tester/MaximumSumMatchingNodes.cpp.obj -MF CMakeFiles\MaximumSumMatchingNodes.dir\Tester\MaximumSumMatchingNodes.cpp.obj.d -o CMakeFiles\MaximumSumMatchingNodes.dir\Tester\MaximumSumMatchingNodes.cpp.obj -c C:\Users\ricky\CompetitiveProgramming\Tester\MaximumSumMatchingNodes.cpp

CMakeFiles/MaximumSumMatchingNodes.dir/Tester/MaximumSumMatchingNodes.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/MaximumSumMatchingNodes.dir/Tester/MaximumSumMatchingNodes.cpp.i"
	C:\Users\ricky\AppData\Local\Programs\CLion\bin\mingw\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\ricky\CompetitiveProgramming\Tester\MaximumSumMatchingNodes.cpp > CMakeFiles\MaximumSumMatchingNodes.dir\Tester\MaximumSumMatchingNodes.cpp.i

CMakeFiles/MaximumSumMatchingNodes.dir/Tester/MaximumSumMatchingNodes.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/MaximumSumMatchingNodes.dir/Tester/MaximumSumMatchingNodes.cpp.s"
	C:\Users\ricky\AppData\Local\Programs\CLion\bin\mingw\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\ricky\CompetitiveProgramming\Tester\MaximumSumMatchingNodes.cpp -o CMakeFiles\MaximumSumMatchingNodes.dir\Tester\MaximumSumMatchingNodes.cpp.s

# Object files for target MaximumSumMatchingNodes
MaximumSumMatchingNodes_OBJECTS = \
"CMakeFiles/MaximumSumMatchingNodes.dir/Tester/MaximumSumMatchingNodes.cpp.obj"

# External object files for target MaximumSumMatchingNodes
MaximumSumMatchingNodes_EXTERNAL_OBJECTS =

MaximumSumMatchingNodes.exe: CMakeFiles/MaximumSumMatchingNodes.dir/Tester/MaximumSumMatchingNodes.cpp.obj
MaximumSumMatchingNodes.exe: CMakeFiles/MaximumSumMatchingNodes.dir/build.make
MaximumSumMatchingNodes.exe: CMakeFiles/MaximumSumMatchingNodes.dir/linkLibs.rsp
MaximumSumMatchingNodes.exe: CMakeFiles/MaximumSumMatchingNodes.dir/objects1.rsp
MaximumSumMatchingNodes.exe: CMakeFiles/MaximumSumMatchingNodes.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Users\ricky\CompetitiveProgramming\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable MaximumSumMatchingNodes.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\MaximumSumMatchingNodes.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MaximumSumMatchingNodes.dir/build: MaximumSumMatchingNodes.exe
.PHONY : CMakeFiles/MaximumSumMatchingNodes.dir/build

CMakeFiles/MaximumSumMatchingNodes.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\MaximumSumMatchingNodes.dir\cmake_clean.cmake
.PHONY : CMakeFiles/MaximumSumMatchingNodes.dir/clean

CMakeFiles/MaximumSumMatchingNodes.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\ricky\CompetitiveProgramming C:\Users\ricky\CompetitiveProgramming C:\Users\ricky\CompetitiveProgramming\cmake-build-debug C:\Users\ricky\CompetitiveProgramming\cmake-build-debug C:\Users\ricky\CompetitiveProgramming\cmake-build-debug\CMakeFiles\MaximumSumMatchingNodes.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/MaximumSumMatchingNodes.dir/depend

