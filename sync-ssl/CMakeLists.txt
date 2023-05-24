project(http)

set(SOURCES http_client_sync_ssl.cpp)
include_directories("../cert/")

add_library(httplib ${SOURCES})

target_include_directories(httplib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})