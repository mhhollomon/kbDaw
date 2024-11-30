# lib

cmake_minimum_required(VERSION 3.20)

add_library(lib-include INTERFACE)

target_include_directories(lib-include INTERFACE .)

add_subdirectory(Model)

add_subdirectory(AudioEngine)

add_subdirectory(GUI)
