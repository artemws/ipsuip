set(SOURCES 
  # countries.cpp countries.h gui/countries.ui
  # mainland.cpp mainland.h gui/mainland.ui
  # mainwindow.cpp mainwindow.h gui/mainwindow.ui
main.cpp)

# set(Boost_USE_STATIC_LIBS ON) # only find static libs set(Boost_USE_DEBUG_LIBS
# ON) # ignore debug libs and set(Boost_USE_RELEASE_LIBS OFF) # only find
# release libs set(Boost_USE_MULTITHREADED ON) set(Boost_USE_STATIC_RUNTIME ON)
# find_package( Boost COMPONENTS # thread REQUIRED)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
message("cmake_cxx_standard: ${CMAKE_CXX_STANDARD}")
qt_standard_project_setup()


# add_subdirectory(gui)
# add_subdirectory(choose_your_fate)
add_subdirectory(functions)
add_subdirectory(http_client)
# add_subdirectory(parallel_parsing)
# add_subdirectory(timer)

# file(GLOB GUI_SOURCES ./gui/*.cpp ./gui/*.h ./gui/*.ui)
# message("GUI_SOURCES: ${GUI_SOURCES}")
# qt6_add_executable(ipsuip ${SOURCES})
# qt6_add_executable(ipsuip ${GUI_SOURCES})
qt6_add_executable(ipsuip 
  gui/mainwindow.ui
  gui/mainwindow.cpp
  gui/mainwindow.h
  gui/countries.ui
  gui/countries.cpp
  gui/countries.h
  gui/mainland.ui
  gui/mainland.cpp
  gui/mainland.h
  main.cpp
  )
# target_link_libraries(ipsuip PUBLIC choose_your_fate -lpthread -lm -static-libgcc -static-libstdc++)
# target_link_libraries(ipsuip PRIVATE Qt6::Widgets ${Boost_LIBRARIES} ${OPENSSL_LIBRARIES})

# target_link_libraries(ipsuip PRIVATE ${Boost_LIBRARIES} )
# target_include_directories(ipsuip PUBLIC build/Desktop_Qt_6_10_1-Debug/src/gui/gui_autogen/include)
target_link_libraries(ipsuip PRIVATE functions Qt6::Core Qt6::Widgets)

message("Boost_libraries: ${Boost_LIBRARIES}")
message("Openssl_libraries: ${OPENSSL_LIBRARIES}")

install(
  TARGETS ipsuip
  BUNDLE DESTINATION .
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
