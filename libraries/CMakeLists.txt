cmake_minimum_required(VERSION 3.16)

project(party)

add_library(party_lib 
    STATIC
        guests.cpp
        party.cpp
)