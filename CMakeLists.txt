cmake_minimum_required(VERSION 3.20)
project(ipsuip)

<<<<<<< HEAD
project(
  ipsuip
  VERSION 0.1
  LANGUAGES CXX)

=======
>>>>>>> refs/remotes/origin/master
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

<<<<<<< HEAD


# set(SOURCES)

# message("Source files: ${SOURCES}")

# set(HEADERS)

# message("Headers: ${HEADERS}")

find_package(
  Boost
  COMPONENTS # thread
  REQUIRED)

set(Boost_USE_STATIC_LIBS ON) # only find static libs
set(Boost_USE_DEBUG_LIBS ON) # ignore debug libs and
set(Boost_USE_RELEASE_LIBS OFF) # only find release libs
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME ON)

find_package(OpenSSL)
set(OPENSSL_USE_STATIC_LIBS ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
message("cmake_cxx_standard: ${CMAKE_CXX_STANDARD}")
qt_standard_project_setup()

# add_subdirectory(sync-ssl)

# qt_wrap_ui(SOURCES mainwindow.ui)

# add_library(mainland STATIC) add_library(country STATIC)

# qt_add_executable( add_executable(
qt6_add_executable(
  ipsuip
  # MANUAL_FINALIZATION ${SOURCES} ${HEADERS}
  main.cpp
  # timer.cpp
  functions.h
  # timer.h
  mainwindow.h
  mainwindow.ui
  mainwindow.cpp
  # choose_your_fate.h
  mainland.h
  mainland.ui
  mainland.cpp
  countries.h
  countries.ui
  countries.cpp)

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

install(
  TARGETS ipsuip
  BUNDLE DESTINATION .
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

# if(QT_VERSION_MAJOR EQUAL 6) qt6_finalize_target(ipsuip) endif()

message("Boost_libraries: ${Boost_LIBRARIES}")
message("Openssl_libraries: ${OPENSSL_LIBRARIES}")
=======
add_subdirectory(src bin)
>>>>>>> refs/remotes/origin/master
