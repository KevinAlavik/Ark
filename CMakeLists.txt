cmake_minimum_required(VERSION 3.21)

project(Ark VERSION 1.0
        DESCRIPTION "Ark is a Codesign framework for iOS"
        LANGUAGES C)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
find_package(OpenSSL REQUIRED)

include_directories(${OPENSSL_INCLUDE_DIR})
file(GLOB PROJECT_SOURCES ${PROJECT_SOURCE_DIR}/*.c)

add_executable(ark ${PROJECT_SOURCES})
target_link_libraries(ark OpenSSL::SSL OpenSSL::Crypto)
