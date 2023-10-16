add_library(choose_your_fate choose_your_fate.cpp choose_your_fate.h)

target_link_libraries(choose_your_fate PRIVATE functions)
target_link_libraries(choose_your_fate PRIVATE timer)
target_include_directories(choose_your_fate PUBLIC .)
