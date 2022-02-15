cmake_minimum_required(VERSION 3.8.0)

## Initialize project
project("server.exe" CXX)
set(TARGET "server.exe")

## Get LibBoost
include(FetchContent)
FetchContent_Declare(
    boost
    URL "https://boostorg.jfrog.io/artifactory/main/release/1.78.0/source/boost_1_78_0.tar.gz"
)
FetchContent_MakeAvailable(boost)

## Set LibBoost variables
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME ON) 

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

## Add link directories
target_link_directories(${TARGET} PRIVATE "Build/_deps/libboost-src/libs/" "/usr/local/lib")

## Link Dependencies
target_link_libraries(${TARGET} filesystem beast boost)

###################
##### TESTING #####
###################

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
