cmake_minimum_required(VERSION 3.16)

set(LIBRARIES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libraries")

set(CMAKE_CXX_STANDARD 23)
enable_testing()

# Conan 2 integration (CMakeDeps + CMakeToolchain)
# The toolchain file is passed from the "conan install" step (see README).
# After that we just rely on find_package with CONFIG mode to load dependencies.
find_package(ut REQUIRED CONFIG)

add_subdirectory(libraries)
add_subdirectory(science_party) # main project
add_subdirectory(unit_tests)