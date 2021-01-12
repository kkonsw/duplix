set(target tests)

set(CATCH_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/3rdparty/catch2)
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})

include_directories(${SOURCE_DIR} ${3RD_PARTY_SOURCE_DIR})

FILE(GLOB hdrs "*.h")
FILE(GLOB srcs "*.cpp")

add_executable(${target} ${hdrs} ${srcs})
target_link_libraries(${target} Catch)
