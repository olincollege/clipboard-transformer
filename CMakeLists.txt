# Require the CMake version matching what is included in the latest LTS version
# of Ubuntu, which at the time of writing is 22.04.
cmake_minimum_required(VERSION 3.22)

# TODO: Define a good project in the line below. If applicable, list other
# languages in this project managed by CMake.
if (APPLE)
    project(clipboard_transformer
            VERSION 1.0
            LANGUAGES CXX OBJC C
            )
else ()
    project(clipboard_transformer
            VERSION 1.0
            LANGUAGES CXX C
            )
endif ()

# Use the latest C standard supported by Clang and LLVM in the latest LTS
# version of Ubuntu.
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_C_FLAGS "-Wall -Wextra")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pedantic")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wconversion")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wdouble-promotion")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wduplicated-branches")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wduplicated-cond")
# The following line is only needed in LLVM/clang
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wimplicit-fallthrough")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wlogical-op")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wmisleading-indentation")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wnull-dereference")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wshadow")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wsign-conversion")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wunreachable-code")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wunused")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")

# No options are set here because the configuration is set in .clang-tidy
# instead. If that file is not present, clang-tidy will be of limited help.
#set(CMAKE_C_CLANG_TIDY "clang-tidy")

# In current courses that teach C, we use the Criterion testing framework. If
# If you want to use a different framework, or if you want to skip testing
# entirely (not recommended), change the lines below.
include(CTest)
find_library(CRITERION criterion REQUIRED)
set(CRITERION_FLAGS --verbose -j1)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK REQUIRED gtk+-3.0)

include_directories(${GTK_INCLUDE_DIRS})
link_directories(${GTK_LIBRARY_DIRS})
add_definitions(${GTK_CFLAGS_OTHER})

# Include the source files.
add_subdirectory(src)

# Include the transform files.
add_subdirectory(transformations)

target_link_libraries(clipboard_transformer ${GTK_LIBRARIES})
