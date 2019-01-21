cmake_minimum_required(VERSION 2.8.12)
project(puredatapy-proj)

include_directories(../src)

include_directories(..)
include_directories(../distrib/variant/include)
include_directories(../pd)
include_directories(../src)

add_subdirectory(pybind11)
add_subdirectory(.. "xpd")

pybind11_add_module(puredatapy wrapper.cpp)
target_link_libraries(puredatapy PRIVATE xpd_static)
