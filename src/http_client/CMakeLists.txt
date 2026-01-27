find_package(OpenSSL)
set(OPENSSL_USE_STATIC_LIBS ON)

add_library(http_client_sync_ssl http_client_sync_ssl.cpp
                                 http_client_sync_ssl.h root_certificates.h)

target_link_libraries(http_client_sync_ssl PRIVATE functions)
target_link_libraries(http_client_sync_ssl PRIVATE ${OPENSSL_LIBRARIES})
target_include_directories(http_client_sync_ssl PUBLIC .)
