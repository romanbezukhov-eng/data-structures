add_library(ds INTERFACE
        TMinStack.h
        ../tests/test_vector.cpp
        ../tests/test_stack.cpp
        ../tests/test_queue.cpp
        ../tests/test_minstack.cpp)
target_include_directories(ds INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})