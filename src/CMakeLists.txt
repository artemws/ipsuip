set(SOURCES 
  main.cpp
  gui/MainWindowController.cpp
  gui/MainWindowController.h
)

# Find Qt6 packages with Widgets for QFileDialog
find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick QuickControls2 Widgets)
message("cmake_cxx_standard: ${CMAKE_CXX_STANDARD}")

qt_standard_project_setup()

# Set up the executable
qt_add_executable(ipsuip 
    ${SOURCES}
    ../qml.qrc
)

# Add QML module
qt_add_qml_module(ipsuip
    URI Ipsuip
    VERSION 1.0
    RESOURCE_PREFIX /
    QML_FILES
        qml/MainWindow.qml
        qml/CountriesDialog.qml
        qml/MainlandsDialog.qml
)

# Link Qt modules and libraries
target_link_libraries(ipsuip PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    Qt6::QuickControls2
    Qt6::Widgets
    functions
)

# Add include directories
target_include_directories(ipsuip PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../
)

# Install the target
install(
    TARGETS ipsuip
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Add subdirectories
add_subdirectory(functions)
add_subdirectory(http_client)
