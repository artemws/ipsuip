add_library(functions STATIC functions.cpp functions.h enum_variants.h)

target_link_libraries(functions PUBLIC http_client_sync_ssl)
# target_link_libraries(functions PUBLIC parallel_parsing)
target_include_directories(functions PUBLIC .)
