cmake_minimum_required(VERSION 3.15)
project(wwtbam_sfml)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH /usr/share/SFML/cmake/Modules)
find_package(SFML COMPONENTS graphics audio REQUIRED)

add_executable(wwtbam_sfml main.cpp)

target_link_libraries(wwtbam_sfml sfml-system sfml-window sfml-graphics sfml-audio)