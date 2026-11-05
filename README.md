# data-structures
Data structures for university projects


• How include this structures in next projects

    include(FetchContent)
    FetchContent_Declare(
    ds
    GIT_REPOSITORY https://github.com/romanbezukhov-eng/data-structures.git
    GIT_TAG main
    )
    FetchContent_MakeAvailable(ds)
    
    target_link_libraries(my_lab PRIVATE ds)
