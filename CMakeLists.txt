cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
project(fractals VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
include(SetCompilerWarningAll)

find_package(RE_FLEX REQUIRED)

add_executable(lemon
    tools/lemon/lemon.c
)

add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/infix_parser.cpp
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/lemon -q
        -T${CMAKE_CURRENT_LIST_DIR}/tools/lemon/lempar.c
        -o${CMAKE_CURRENT_BINARY_DIR}/infix_parser.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/infix.yy
    VERBATIM
    DEPENDS lemon src/infix.yy tools/lemon/lempar.c
    COMMENT "[infix] Building parser with lemon"
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

RE_FLEX_TARGET(infix
    src/infix.lex
    ${CMAKE_CURRENT_BINARY_DIR}/infix_lexer.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/infix_lexer.hpp
)

add_executable(fractals
    src/fractals.cpp
    src/driver.cpp
    src/parse_tree.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/infix_parser.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/infix_lexer.cpp
)

target_include_directories(fractals
  PRIVATE
  include
    ${CMAKE_CURRENT_BINARY_DIR}
    ${RE_FLEX_INCLUDE_DIR}
)
target_link_libraries(fractals
    ${RE_FLEX_LIBRARIES}
)
set_property(TARGET fractals
    PROPERTY CXX_STANDARD 17
)
set_property(TARGET fractals
    PROPERTY CXX_STANDARD_REQUIRED ON
)
