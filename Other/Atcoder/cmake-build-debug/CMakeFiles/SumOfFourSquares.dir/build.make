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
include CMakeFiles/SumOfFourSquares.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/SumOfFourSquares.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/SumOfFourSquares.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SumOfFourSquares.dir/flags.make

CMakeFiles/SumOfFourSquares.dir/codegen:
.PHONY : CMakeFiles/SumOfFourSquares.dir/codegen

CMakeFiles/SumOfFourSquares.dir/SumOfFourSquares.cpp.obj: CMakeFiles/SumOfFourSquares.dir/flags.make
CMakeFiles/SumOfFourSquares.dir/SumOfFourSquares.cpp.obj: C:/Users/ricky/CompetitiveProgramming/SumOfFourSquares.cpp
CMakeFiles/SumOfFourSquares.dir/SumOfFourSquares.cpp.obj: CMakeFiles/SumOfFourSquares.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\ricky\CompetitiveProgramming\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/SumOfFourSquares.dir/SumOfFourSquares.cpp.obj"
	C:\Users\ricky\AppData\Local\Programs\CLion\bin\mingw\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/SumOfFourSquares.dir/SumOfFourSquares.cpp.obj -MF CMakeFiles\SumOfFourSquares.dir\SumOfFourSquares.cpp.obj.d -o CMakeFiles\SumOfFourSquares.dir\SumOfFourSquares.cpp.obj -c C:\Users\ricky\CompetitiveProgramming\SumOfFourSquares.cpp

CMakeFiles/SumOfFourSquares.dir/SumOfFourSquares.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/SumOfFourSquares.dir/SumOfFourSquares.cpp.i"
	C:\Users\ricky\AppData\Local\Programs\CLion\bin\mingw\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\ricky\CompetitiveProgramming\SumOfFourSquares.cpp > CMakeFiles\SumOfFourSquares.dir\SumOfFourSquares.cpp.i

CMakeFiles/SumOfFourSquares.dir/SumOfFourSquares.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/SumOfFourSquares.dir/SumOfFourSquares.cpp.s"
	C:\Users\ricky\AppData\Local\Programs\CLion\bin\mingw\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\ricky\CompetitiveProgramming\SumOfFourSquares.cpp -o CMakeFiles\SumOfFourSquares.dir\SumOfFourSquares.cpp.s

# Object files for target SumOfFourSquares
SumOfFourSquares_OBJECTS = \
"CMakeFiles/SumOfFourSquares.dir/SumOfFourSquares.cpp.obj"

# External object files for target SumOfFourSquares
SumOfFourSquares_EXTERNAL_OBJECTS =

SumOfFourSquares.exe: CMakeFiles/SumOfFourSquares.dir/SumOfFourSquares.cpp.obj
SumOfFourSquares.exe: CMakeFiles/SumOfFourSquares.dir/build.make
SumOfFourSquares.exe: CMakeFiles/SumOfFourSquares.dir/linkLibs.rsp
SumOfFourSquares.exe: CMakeFiles/SumOfFourSquares.dir/objects1.rsp
SumOfFourSquares.exe: CMakeFiles/SumOfFourSquares.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Users\ricky\CompetitiveProgramming\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable SumOfFourSquares.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\SumOfFourSquares.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/SumOfFourSquares.dir/build: SumOfFourSquares.exe
.PHONY : CMakeFiles/SumOfFourSquares.dir/build

CMakeFiles/SumOfFourSquares.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\SumOfFourSquares.dir\cmake_clean.cmake
.PHONY : CMakeFiles/SumOfFourSquares.dir/clean

CMakeFiles/SumOfFourSquares.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\ricky\CompetitiveProgramming C:\Users\ricky\CompetitiveProgramming C:\Users\ricky\CompetitiveProgramming\cmake-build-debug C:\Users\ricky\CompetitiveProgramming\cmake-build-debug C:\Users\ricky\CompetitiveProgramming\cmake-build-debug\CMakeFiles\SumOfFourSquares.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/SumOfFourSquares.dir/depend

