set(target ${PROJECT_NAME})

include_directories(${SOURCE_DIR})

FILE(GLOB hdrs "*.h")
FILE(GLOB srcs "*.cpp")

add_executable(${target} ${hdrs} ${srcs})
target_link_libraries(${target} ${DUPLIX_LIBRARY})
