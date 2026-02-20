# functions должен быть первым — http_client зависит от functions.h
add_subdirectory(functions)
add_subdirectory(http_client)

add_executable(ipsuip main.cpp)

target_include_directories(ipsuip PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/functions
    ${CMAKE_CURRENT_SOURCE_DIR}/http_client
    ${IPSUIP_BOOST_INCLUDE_DIRS}
)

target_link_libraries(ipsuip PRIVATE
    functions
    http_client_sync_ssl
    ${IPSUIP_OPENSSL_LIBRARIES}
    ${IPSUIP_BOOST_LIBRARIES}
)

if(BUILD_STATIC AND UNIX AND NOT APPLE)
    target_link_options(ipsuip PRIVATE -static-libgcc -static-libstdc++)
endif()

install(TARGETS ipsuip RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
