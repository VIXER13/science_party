cmake_minimum_required(VERSION 3.16)

project(unit_tests)

add_executable(unit_tests
    main.cpp
    guests.cpp
    party.cpp
    utils.cpp
)

target_include_directories(
    unit_tests
    PRIVATE #
        ${LIBRARIES_DIR}
)

target_link_libraries(
    unit_tests
    PRIVATE
        Boost::ut
        party_lib
)

add_test(NAME unit_tests COMMAND unit_tests)