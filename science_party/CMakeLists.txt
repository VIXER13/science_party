cmake_minimum_required(VERSION 3.16)

project(science_party)

add_executable(science_party main.cpp)

target_include_directories(
    science_party
    PRIVATE
        ${LIBRARIES_DIR}
)

target_link_libraries(
    science_party
    PRIVATE
        party_lib
)
