cmake_minimum_required(VERSION 3.20)

project(
  ipsuip
  VERSION 0.1
  LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -Wall -Wextra -Wpedantic
# -Wno-unused-parameter")

message("cmake_cxx_standard: ${CMAKE_CXX_STANDARD}")

set(SOURCES main.cpp functions.cpp timer.cpp choose_your_fate.cpp
            http_client_sync_ssl.cpp)

message("Source files: ${SOURCES}")

set(HEADERS
    functions.h
    countries.h
    timer.h
    enum_variants.h
    parallel_parsing.h
    choose_your_fate.h
    http_client_sync_ssl.h)

message("Headers: ${HEADERS}")

set(Boost_USE_STATIC_LIBS ON) # only find static libs
set(Boost_USE_DEBUG_LIBS ON) # ignore debug libs and
set(Boost_USE_RELEASE_LIBS OFF) # only find release libs
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME ON)

find_package(
  Boost
  COMPONENTS # thread
  REQUIRED)

find_package(OpenSSL)
set(OPENSSL_USE_STATIC_LIBS ON)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# add_subdirectory(sync-ssl)

qt_add_executable(ipsuip ${SOURCES} ${HEADERS} mainwindow.h mainwindow.cpp
                  mainwindow.ui)

target_link_libraries(ipsuip PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
                                     ${Boost_LIBRARIES} ${OPENSSL_LIBRARIES})
set_target_properties(
  ipsuip
  PROPERTIES MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
             MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
             MACOSX_BUNDLE_SHORT_VERSION_STRING
             ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
             MACOSX_BUNDLE TRUE
             WIN32_EXECUTABLE TRUE)

message("Boost_libraries: ${Boost_LIBRARIES}")
message("Openssl_libraries: ${OPENSSL_LIBRARIES}")
