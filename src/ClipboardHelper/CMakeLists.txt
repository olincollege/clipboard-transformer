if(APPLE)
    # on macOS, we need to link against the AppKit framework
    find_library(APPKIT_LIBRARY AppKit)

    add_library(ClipboardHelper ClipboardHelper.h DarwinClipboardHelper.mm)

    target_link_libraries(ClipboardHelper ${APPKIT_LIBRARY})
else()
    add_library(ClipboardHelper ClipboardHelper.h UbuntuClipboardHelper.cpp)
endif()
