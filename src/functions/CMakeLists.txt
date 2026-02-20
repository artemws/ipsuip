add_library(functions STATIC functions.cpp functions.h enum_variants.h)

target_include_directories(functions PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${IPSUIP_BOOST_INCLUDE_DIRS}
)

target_link_libraries(functions PUBLIC
    http_client_sync_ssl
    ${IPSUIP_BOOST_LIBRARIES}
)
