cmake_minimum_required(VERSION 3.23)
project(hdrplus)

set(CMAKE_CXX_STANDARD 23)

find_package(OpenMP REQUIRED)

message(STATUS "OpenMP Configuration: ${OpenMP_CXX_INCLUDE_DIRS}:${OpenMP_CXX_LIBRARIES}")
message(STATUS "Boost Configuration: ${Boost_INCLUDE_DIRS}:${Boost_LIBRARIES}")
option(ENABLE_AMDGPU_OFFLOAD "Enable AMDGPU Offload" OFF)
option(ENABLE_CUDA_OFFLOAD "Enable CUDA Offload" OFF)

add_library(hdrplus SHARED src/main.cpp)

if (CMAKE_BUILD_TYPE STREQUAL "Release" OR CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    target_compile_options(hdrplus PRIVATE -march=native -mfma -Ofast -ffast-math -flto)
    target_link_options(hdrplus PRIVATE -flto)
    message(STATUS "Set full optimization: ${CMAKE_CXX_FLAGS}")
endif()

target_include_directories(hdrplus PUBLIC ${OpenMP_CXX_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})
target_link_libraries(hdrplus PUBLIC ${OpenMP_CXX_LIBRARIES} ${Boost_LIBRARIES})
target_compile_options(hdrplus PUBLIC ${OpenMP_CXX_FLAGS})

if (ENABLE_AMDGPU_OFFLOAD)
    set(CMAKE_CXX_FLAGS "-fopenmp=libomp -fopenmp-targets=amdgcn ${CMAKE_CXX_FLAGS}")
    target_compile_options(hdrplus PUBLIC -rtlib=libgcc -unwindlib=libgcc -stdlib=libstdc++)
    target_link_libraries(hdrplus PUBLIC omptarget.rtl.amdgpu omptarget -rtlib=libgcc -unwindlib=libgcc -stdlib=libstdc++)
endif ()

if (ENABLE_CUDA_OFFLOAD)
    set(CMAKE_CXX_FLAGS "-fopenmp=libomp -fopenmp-targets=nvptx64 ${CMAKE_CXX_FLAGS}")
    target_compile_options(hdrplus PUBLIC -rtlib=libgcc -unwindlib=libgcc -stdlib=libstdc++)
    target_link_libraries(hdrplus PUBLIC omptarget.rtl.cuda omptarget -rtlib=libgcc -unwindlib=libgcc -stdlib=libstdc++)
endif ()

add_subdirectory(contrib)