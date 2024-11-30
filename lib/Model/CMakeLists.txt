# lib/Model

cmake_minimum_required(VERSION 3.20)

add_library(Model OBJECT)

target_sources(Model
    PRIVATE
        FullModel.cpp
    INTERFACE
        "Model.hpp"
        FullModel.hpp
    )

target_link_libraries(Model lib-include wx::base sqlite3 sqlite_modern_cpp)

set_target_properties(Model PROPERTIES
COMPILE_FLAGS "/D \"SQLITE_VERSION_NUMBER=${SQLITE_VERSION_NUMBER}\" /D _MBCS /GR"
)
