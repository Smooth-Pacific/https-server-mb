cmake_minimum_required(VERSION 3.8.0)

## Initialize project
project("client.exe" CXX)
set(TARGET "client.exe")

## Include directories
include_directories(${TARGET} ${CMAKE_SOURCE_DIR}/Includes)
include_directories(${TARGET} ${CMAKE_SOURCE_DIR}/Tests)
set(INCLUDE_DIR Includes)

## Source directories
set(SOURCE_DIR Sources)

## Add CXX sources
set(SOURCES
    # CXX sources
    ${SOURCE_DIR}/Main.cpp
    # CXX includes
    ${INCLUDE_DIR}/Include.hpp
)

## Set output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Bin)

## Application executable and link dependencies
add_executable(${TARGET} ${SOURCES})

## Add testing support
#project("run-tests" CXX)
#set(TESTS "run-tests")

## Include directories
#include_directories(${TESTS} ${CMAKE_CURRENT_BINARY_DIR}/Includes)
#include_directories(${TESTS} ${CMAKE_CURRENT_BINARY_DIR}/Tests)

## Source directories
#set(TESTS_DIR Tests)

## Add CXX sources
#set(TEST_SOURCES
    ## CXX sources
    #${TESTS_DIR}/TestSuite.cpp
    ## CXX includes
    #${INCLUDE_DIR}/Sentence.hpp
    #${TESTS_DIR}/TestSuite.hpp
#)

## Test executable and link dependencies
#add_executable(${TESTS} ${TEST_SOURCES} ${PROTO_SRCS}) 
#target_link_libraries(${TESTS} ${Protobuf_LIBRARIES})
