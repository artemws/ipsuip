cmake_minimum_required(VERSION 3.30)

project(ipsuip VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

cmake_policy(SET CMP0167 NEW)

add_subdirectory(src)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Find required Qt packages
# find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick QuickControls2 Widgets)
# target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core Qt6::Gui Qt6::Qml Qt6::Quick Qt6::QuickControls2)

# Collect source files
# file(GLOB GUI_SOURCES ./*.cpp ./*.h)

# Create the executable
# add_executable(${PROJECT_NAME} ${GUI_SOURCES} main.cpp)

# Link Qt libraries
# qt_standard_project_setup()

# Add QML module
# qt_add_qml_module(${PROJECT_NAME}
#     URI ipsuip
#     VERSION 1.0
#     QML_FILES
#         qml/MainWindow.qml
#         qml/Countries.qml
#         qml/Mainland.qml
#         qml/CheckBox.qml
# )

# Include directories
# target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Link libraries
# target_link_libraries(${PROJECT_NAME} PRIVATE
#     Qt6::Core
#     Qt6::Gui
#     Qt6::Qml
#     Qt6::Quick
#     Qt6::QuickControls2
# )
