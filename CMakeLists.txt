cmake_minimum_required(VERSION 3.15)
project(wwtbam_sfml)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH /usr/share/SFML/cmake/Modules)
find_package(SFML COMPONENTS graphics audio REQUIRED)

add_executable(wwtbam_sfml main.cpp ResourceHolder.cpp ResourceHolder.h wwtbam_core/Question.cpp wwtbam_core/Question.h Group.cpp Group.h Button.cpp Button.h TexturedButton.cpp TexturedButton.h wwtbam_core/LongButton.cpp wwtbam_core/LongButton.h wwtbam_core/WindowResolution.h)

target_link_libraries(wwtbam_sfml sfml-system sfml-window sfml-graphics sfml-audio)