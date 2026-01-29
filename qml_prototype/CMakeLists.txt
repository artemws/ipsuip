# qml_prototype/CMakeLists.txt
cmake_minimum_required(VERSION 3.23)
project(IpsuipQmlPrototype LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt6 packages
find_package(Qt6 REQUIRED COMPONENTS Core Gui Quick QuickControls2 Qml)

# Set up the executable
qt_add_executable(ipsuip_qml_prototype
    main.cpp
)

# Set up QML import paths
qt_add_qml_module(ipsuip_qml_prototype
    URI IpsuipPrototype
    VERSION 1.0
    QML_FILES
        main.qml
        components/Countries.qml
        components/Mainland.qml
        components/styles/Theme.qml
)

# Link Qt modules
target_link_libraries(ipsuip_qml_prototype PRIVATE
    Qt6::Core
    Qt6::Quick
    Qt6::QuickControls2
    Qt6::Qml
)

# Install the target
install(TARGETS ipsuip_qml_prototype
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)