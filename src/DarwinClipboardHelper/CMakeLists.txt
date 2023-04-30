# on macOS, we need to link against the AppKit framework
find_library(APPKIT_LIBRARY AppKit)

add_library(DarwinClipboardHelper DarwinClipboardHelper.h DarwinClipboardHelper.mm)

target_link_libraries(DarwinClipboardHelper ${APPKIT_LIBRARY})
