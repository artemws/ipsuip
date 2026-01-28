add_library(choose_your_fate STATIC choose_your_fate.cpp choose_your_fate.h)

target_link_libraries(choose_your_fate PUBLIC functions)
target_link_libraries(choose_your_fate PRIVATE timer)
target_include_directories(choose_your_fate PUBLIC .)
