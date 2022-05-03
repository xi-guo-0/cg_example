cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 20)
project(cg_example)
include(FetchContent)
FetchContent_Declare(
        libpng
        GIT_REPOSITORY https://github.com/glennrp/libpng.git
        GIT_TAG v1.6.37
)
set(PNG_SHARED ON CACHE BOOL "" FORCE)
set(PNG_STATIC OFF CACHE BOOL "" FORCE)
set(PNG_EXECUTABLES OFF CACHE BOOL "" FORCE) # we only want lib
set(PNG_TESTS OFF CACHE BOOL "" FORCE) # we only want lib
set(SKIP_INSTALL_ALL OFF CACHE BOOL "" FORCE) # we only want lib
set(PNG_ARM_NEON off)
FetchContent_MakeAvailable(libpng)
include_directories(
        ${libpng_SOURCE_DIR}
        ${libpng_BINARY_DIR}
)
add_subdirectory(src)