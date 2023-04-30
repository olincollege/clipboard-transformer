# Disable clip examples and tests
set(CLIP_EXAMPLES OFF CACHE BOOL "Compile clip examples")
set(CLIP_TESTS OFF CACHE BOOL "Compile clip tests")

# Add clip subdirectory to compile the library
add_subdirectory(clip)

add_library(gui gui.h gui.cpp)
add_library(transform transformation.h transformation.cpp)

add_executable(clipboard_transformer main.cpp)

target_link_libraries(clipboard_transformer clip gui transform)

if (APPLE)
    add_subdirectory(DarwinClipboardHelper)
    target_link_libraries(clipboard_transformer DarwinClipboardHelper)
endif ()
