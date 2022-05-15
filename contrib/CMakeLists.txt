find_package(Boost REQUIRED COMPONENTS program_options system)

set(ABSL_PROPAGATE_CXX_STD ON CACHE BOOL "abseil-cpp" FORCE)

add_subdirectory(abseil-cpp)
add_subdirectory(snmalloc)
add_subdirectory(googletest)


