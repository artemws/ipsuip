project(cert)

set(SOURCES root_certificates.cpp)
set(HEADERS root_certificates.h)

add_library(certlib ${SOURCES} ${HEADERS})

target_include_directories(certlib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})