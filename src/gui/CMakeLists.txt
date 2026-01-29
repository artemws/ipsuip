

file(GLOB GUI_SOURCES ./*.cpp ./*.h)

# Добавляем поддержку QML и Quick
find_package(Qt6 REQUIRED COMPONENTS Quick Qml)

# Создаем статическую библиотеку для GUI
add_library(gui STATIC ${GUI_SOURCES})

# Линкуем библиотеки Qt
target_link_libraries(gui PUBLIC Qt6::Quick Qt6::Qml Qt6::Core Qt6::Gui functions)

# Указываем директорию для QML-файлов
qt_add_qml_module(gui
    URI ipsuip
    VERSION 1.0
    QML_FILES
        MainWindow.qml
        Countries.qml
        Mainland.qml
)

# Указываем директории для заголовочных файлов
target_include_directories(gui PUBLIC .)

message("GUI_SOURCES: ${GUI_SOURCES}")
