

file(GLOB GUI_SOURCES ./*.cpp ./*.h ./*.ui)
add_library(gui STATIC ${GUI_SOURCES})
target_link_libraries(gui PUBLIC Qt6::Widgets functions)
target_include_directories(gui PUBLIC .)

message("GUI_SOURCES: ${GUI_SOURCES}")
