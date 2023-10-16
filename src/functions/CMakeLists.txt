add_library(functions functions.cpp functions.h countries.h enum_variants.h)

target_link_libraries(functions PRIVATE http_client_sync_ssl)
target_link_libraries(functions PRIVATE parallel_parsing)
target_include_directories(functions PUBLIC .)
