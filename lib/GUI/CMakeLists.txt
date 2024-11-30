# lib/AudioEngine

cmake_minimum_required(VERSION 3.20)

add_library(GUI OBJECT)

target_sources(GUI
    PRIVATE
        "AppFrame.cpp"
        "TimeLine.cpp"
    INTERFACE
        "AppFrame.hpp"
        "TimeLine.hpp"
    )

target_link_libraries(GUI wx::core wx::base lib-include Model)
