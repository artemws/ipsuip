project(http LANGUAGES CXX)

# add_subdirectory("../cert") include_directories("../cert") message("Include
# diretory: ${INCLUDE_DIRECTORIES}") include("../cert")

set(SOURCES http_client_sync_ssl.cpp root_certificates.h)

add_library(httplib STATIC ${SOURCES})

# target_include_directories(httplib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
# target_include_directories(certlib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
