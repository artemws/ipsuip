add_library(parallel_parsing STATIC parallel_parsing.cpp parallel_parsing.h)

target_link_libraries(parallel_parsing PRIVATE functions)

target_include_directories(parallel_parsing PUBLIC .)
