cmake_minimum_required(VERSION 3.28)
project(CompetitiveProgramming)

set(CMAKE_CXX_STANDARD 17)

file(GLOB CPP_FILES "*.cpp")
foreach(CPP_FILE ${CPP_FILES})
    get_filename_component(EXECUTABLE_NAME ${CPP_FILE} NAME_WE)
    add_executable(${EXECUTABLE_NAME} ${CPP_FILE})
endforeach()

file(GLOB NOTES_CPP_FILES "Notes/*.cpp")
foreach(CPP_FILE ${NOTES_CPP_FILES})
    get_filename_component(EXECUTABLE_NAME ${CPP_FILE} NAME_WE)
    add_executable(NOTE_${EXECUTABLE_NAME} ${CPP_FILE}) # Prefix 'NOTE_'
endforeach()
