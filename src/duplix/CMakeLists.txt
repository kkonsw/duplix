set(target ${DUPLIX_LIBRARY})

include_directories(${SOURCE_DIR})

# openssl
find_package(OpenSSL REQUIRED)

FILE(GLOB hdrs "*.h")
FILE(GLOB srcs "*.cpp")

add_library(${target} STATIC ${srcs} ${hdrs})
target_link_libraries(${target} OpenSSL::Crypto)
