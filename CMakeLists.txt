cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
project(fractals VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
include(SetCompilerWarningAll)

add_executable(lemon
    tools/lemon/lemon.c
)

add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/infix.cpp
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/lemon -q
        -T${CMAKE_CURRENT_LIST_DIR}/tools/lemon/lempar.c
        -o${CMAKE_CURRENT_BINARY_DIR}/infix.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/infix.yy
    VERBATIM
    DEPENDS lemon src/infix.yy tools/lemon/lempar.c
    COMMENT "[infix] Building parser with lemon"
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

add_executable(fractals
    src/fractals.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/infix.cpp
)
target_include_directories(fractals
  PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}
)
set_property(TARGET fractals
    PROPERTY CXX_STANDARD 17
)
set_property(TARGET fractals
    PROPERTY CXX_STANDARD_REQUIRED ON
)
