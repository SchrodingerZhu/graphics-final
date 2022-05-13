cmake_minimum_required(VERSION 3.23)
project(hdrplus)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenMP)
message(STATUS "OpenMP Configuration: ${OpenMP_CXX_INCLUDE_DIRS}:${OpenMP_CXX_LIBRARIES}")
add_executable(hdrplus main.cpp)

if (CMAKE_BUILD_TYPE STREQUAL "Release" OR CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    set(CMAKE_CXX_FLAGS "-flto -march=native -Ofast -ffast-math -mfma -fvisibility=hidden -fvisibility-inlines-hidden ${CMAKE_CXX_FLAGS}")
    message(STATUS "Set full optimization: ${CMAKE_CXX_FLAGS}")
endif()
target_include_directories(hdrplus PUBLIC ${OpenMP_CXX_INCLUDE_DIRS})
target_link_libraries(hdrplus PUBLIC ${OpenMP_CXX_LIBRARIES})
target_compile_options(hdrplus PUBLIC ${OpenMP_CXX_FLAGS})