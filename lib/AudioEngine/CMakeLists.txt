# lib/AudioEngine

cmake_minimum_required(VERSION 3.20)

add_library(AudioEngine OBJECT)

target_sources(AudioEngine
    PRIVATE
        "AudioEngine.cpp"
    INTERFACE
        "AudioEngine.hpp"
    )

target_link_libraries(AudioEngine wx::core wx::base lib-include)
