cmake_minimum_required(VERSION 3.8.0)

## Initialize project
project("utopia-server.exe" CXX)
set(TARGET "utopia-server.exe")

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
    ${INCLUDE_DIR}/HelloResource.hpp
    ${INCLUDE_DIR}/Resources.hpp
    ${INCLUDE_DIR}/RootResource.hpp
    ${INCLUDE_DIR}/ServerOptions.hpp
)

## Set output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Bin)

## Application executable and link dependencies
add_executable(${TARGET} ${SOURCES})

# ------------- TESTING ------------- #

## Add link directories
target_link_directories(${TARGET} PRIVATE /usr/local/lib)

## Link Dependencies
target_link_libraries(${TARGET} httpserver microhttpd)

## Add testing support
project("run-tests" CXX)
set(TESTS "run-tests")

## Include directories
include_directories(${TESTS} ${CMAKE_CURRENT_BINARY_DIR}/Includes)
include_directories(${TESTS} ${CMAKE_CURRENT_BINARY_DIR}/Tests)

## Source directories
set(TESTS_DIR Tests)

## Add CXX sources
set(TEST_SOURCES
    # CXX sources
    ${TESTS_DIR}/TestSuite.cpp
    ${TESTS_DIR}/TestServerOptions.cpp
    # CXX includes
    ${TESTS_DIR}/TestSuite.hpp
    ${TESTS_DIR}/TestServerOptions.hpp
    ${INCLUDE_DIR}/ServerOptions.hpp
    #${INCLUDE_DIR}/HelloResource.hpp
    #${INCLUDE_DIR}/Resources.hpp
    #${INCLUDE_DIR}/RootResource.hpp
)

## Test executable and link dependencies
add_executable(${TESTS} ${TEST_SOURCES}) 

## Link Dependencies
target_link_libraries(${TESTS} httpserver microhttpd)
