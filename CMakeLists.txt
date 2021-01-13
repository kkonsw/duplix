cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME duplix)
project(${PROJECT_NAME})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(3RD_PARTY_SOURCE_DIR ${CMAKE_SOURCE_DIR}/3rdparty)

set(DUPLIX_LIBRARY "duplix-lib")
set(DUPLIX_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/src/duplix)
add_subdirectory(src/duplix)

add_subdirectory(src)
add_subdirectory(tests)
