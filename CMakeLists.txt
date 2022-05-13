cmake_minimum_required(VERSION 3.23)
project(hdrplus)

set(CMAKE_CXX_STANDARD 23)

find_package(OpenMP)
message(STATUS "OpenMP Configuration: ${OpenMP_CXX_INCLUDE_DIRS}:${OpenMP_CXX_LIBRARIES}")
add_executable(hdrplus main.cpp)
option(ENABLE_AMDGPU_OFFLOAD "Enable AMDGPU Offload" OFF)
option(ENABLE_CUDA_OFFLOAD "Enable CUDA Offload" OFF)
if (CMAKE_BUILD_TYPE STREQUAL "Release" OR CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    set(CMAKE_CXX_FLAGS
            "-flto -march=native -mfma -fvisibility=hidden -fvisibility-inlines-hidden -Ofast -ffast-math ${CMAKE_CXX_FLAGS}")
    message(STATUS "Set full optimization: ${CMAKE_CXX_FLAGS}")
endif()

target_include_directories(hdrplus PUBLIC ${OpenMP_CXX_INCLUDE_DIRS})
target_link_libraries(hdrplus PUBLIC ${OpenMP_CXX_LIBRARIES})
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