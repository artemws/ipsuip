add_library(http_client_sync_ssl STATIC
    http_client_sync_ssl.cpp
    http_client_sync_ssl.h
    root_certificates.h
)

target_include_directories(http_client_sync_ssl PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    # functions.h нужен http_client, но functions — отдельная цель;
    # указываем путь напрямую чтобы не зависеть от порядка add_subdirectory
    ${CMAKE_CURRENT_SOURCE_DIR}/../functions
    ${IPSUIP_BOOST_INCLUDE_DIRS}
)

target_link_libraries(http_client_sync_ssl PRIVATE
    ${IPSUIP_OPENSSL_LIBRARIES}
    ${IPSUIP_BOOST_LIBRARIES}
)
