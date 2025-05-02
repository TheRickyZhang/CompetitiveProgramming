cmake_minimum_required(VERSION 3.28)
project(CompetitiveProgramming)

set(CMAKE_CXX_STANDARD 17)

file(GLOB CPP_FILES
        "${CMAKE_SOURCE_DIR}/*.cpp"
        "${CMAKE_SOURCE_DIR}/Tester/*.cpp"
        "${CMAKE_SOURCE_DIR}/Notes_CIS4930/Notes/*.cpp"
)

foreach(_f IN LISTS CPP_FILES)
    get_filename_component(_n ${_f} NAME_WE)

    # prefix if it lives under Notes_CIS4930/Notes
    if(_f MATCHES "Notes_CIS4930/Notes/")
        set(_t NOTE_${_n})
    else()
        set(_t ${_n})
    endif()

    add_executable(${_t} ${_f})
endforeach()
