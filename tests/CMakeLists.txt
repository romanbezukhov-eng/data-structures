include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.tar.gz
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

# нужно только на Windows, на остальных системах не мешает
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(ds_tests
        test_vector.cpp
        test_stack.cpp
        test_queue.cpp
        test_minstack.cpp
)
target_link_libraries(ds_tests PRIVATE ds GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(ds_tests)

