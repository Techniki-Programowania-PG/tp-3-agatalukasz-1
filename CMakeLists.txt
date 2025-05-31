cmake_minimum_required(VERSION 3.14)
project(signal_project)

set(CMAKE_CXX_STANDARD 17)

find_package(pybind11 REQUIRED)

include_directories($ENV{CONDA_PREFIX}/Library/include)

add_subdirectory(matplotplusplus)

add_library(signal_lib src/signal.cpp)

add_executable(main_exec src/main.cpp)
target_link_libraries(main_exec PRIVATE signal_lib matplot)

pybind11_add_module(signal_module src/module.cpp)
target_link_libraries(signal_module PRIVATE signal_lib pybind11::module)
