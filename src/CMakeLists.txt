find_package(OpenSSL REQUIRED)
find_package(Boost REQUIRED COMPONENTS regex)

add_executable(ipsuip main.cpp)

target_link_libraries(ipsuip PRIVATE
    functions
    http_client_sync_ssl
    OpenSSL::SSL
    OpenSSL::Crypto
    Boost::regex
)

target_include_directories(ipsuip PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/functions
    ${CMAKE_CURRENT_SOURCE_DIR}/http_client
)

add_subdirectory(functions)
add_subdirectory(http_client)

install(
    TARGETS ipsuip
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
