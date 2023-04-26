add_subdirectory(ClipboardHelper)

add_library(gui gui.h gui.cpp)
add_library(transform transformation.h transformation.cpp)

add_executable(clipboard_transformer main.cpp)

target_link_libraries(clipboard_transformer ClipboardHelper gui transform)
