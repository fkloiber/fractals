cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(fractals VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
include(SetCompilerWarningAll)

add_executable(fractals
    src/fractals.cpp
)
set_property(TARGET fractals
    PROPERTY CXX_STANDARD 17
)
set_property(TARGET fractals
    PROPERTY CXX_STANDARD_REQUIRED ON
)
