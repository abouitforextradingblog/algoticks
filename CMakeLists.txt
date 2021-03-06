cmake_minimum_required(VERSION 3.0)
project(algoticks VERSION 1.0 LANGUAGES C)
set(CMAKE_C_STANDARD 11)

if (CMAKE_BUILD_TYPE MATCHES Release)
    message("Release Build: Enabling Optimizations (-O3)")
    set(CMAKE_C_FLAGS "-O3")
endif()

#default
set(CMAKE_CURRENT_BINARY_DIR "release")

#if debug in arg, change folder name to "debug"
if(CMAKE_BUILD_TYPE MATCHES Debug)
     set(CMAKE_C_FLAGS "-Wall")
     set(CMAKE_CURRENT_BINARY_DIR "debug")
ENDIF(CMAKE_BUILD_TYPE MATCHES Debug)

#create algo dir
#file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/algorithms)

include_directories(include /usr/include)
include_directories(${PROJECT_SOURCE_DIR})

if (WIN32)
include_directories(C:/vcpkg/installed/x64-windows/include)
link_directories(C:/vcpkg/installed/x64-windows/lib)
endif()

#GLOB all source files!
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.c)

# add algorithm names to this list
list(APPEND algorithms
    Greens
    Reds
    ThreeLineStrike
    ThreeBlackCrows
    TwoBlackGapping
    EveningStar
    AbandonedBaby)

foreach(algo ${algorithms})
message("Building Algorithm:" ${algo})
add_library(${algo} MODULE src/algorithms/${algo}.c)
set_target_properties(${algo}
    PROPERTIES
    PREFIX ""
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/algorithms/
)
endforeach()

add_executable(algoticks ${SRC_FILES})

#link required libs
target_link_libraries(algoticks PRIVATE json-c)

if(NOT WIN32)
     target_link_libraries(algoticks PRIVATE dl)
endif()

#set output to bin/
set_target_properties(algoticks
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/archive/
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib/
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/
)

#copy configs to bin/
file(COPY ${PROJECT_SOURCE_DIR}/assets/config.json
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)
file(COPY ${PROJECT_SOURCE_DIR}/assets/settings.json
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)
file(COPY ${PROJECT_SOURCE_DIR}/assets/benchmark.json
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)
     file(COPY ${PROJECT_SOURCE_DIR}/assets/example.csv
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)