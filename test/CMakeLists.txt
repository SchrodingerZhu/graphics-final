file(GLOB HDR_GTEST_SRC gtest_*.cpp gtest_*.h)
add_executable(gtest_hdr ${HDR_GTEST_SRC})
target_link_libraries(gtest_hdr hdrplus gtest_main)