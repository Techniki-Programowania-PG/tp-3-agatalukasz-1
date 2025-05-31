cmake_minimum_required(VERSION 3.14)
project(signal_project)

set(CMAKE_CXX_STANDARD 17)

# Znajduje pybind11 z Condy
find_package(pybind11 REQUIRED)

# Dodaje ścieżkę do nagłówków pybind11 z Condy
include_directories($ENV{CONDA_PREFIX}/Library/include)

# Dodaje matplotplusplus
add_subdirectory(matplotplusplus)

# Tworzy bibliotekę z logiką sygnałów
add_library(signal_lib src/signal.cpp)

# Tworzy plik wykonywalny main_exec i linkuje bibliotekę + matplot
add_executable(main_exec src/main.cpp)
target_link_libraries(main_exec PRIVATE signal_lib matplot)

# Tworzy moduł Pythona i linkuje pybind11 + signal_lib
pybind11_add_module(signal_module src/module.cpp)
target_link_libraries(signal_module PRIVATE signal_lib pybind11::module)
