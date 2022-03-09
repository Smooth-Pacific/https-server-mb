cmake_minimum_required(VERSION 3.8.0)

## Initialize project
project("utopia-server" CXX)
set(TARGET "utopia-server")

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
    ${SOURCE_DIR}/Authorization.cpp
    ${SOURCE_DIR}/Logger.cpp
    ${SOURCE_DIR}/PerformanceMonitor.cpp
    ${SOURCE_DIR}/ServerOptions.cpp
    # CXX includes
    ${INCLUDE_DIR}/Authorization.hpp
    ${INCLUDE_DIR}/FileResource.hpp
    ${INCLUDE_DIR}/HelloResource.hpp
    ${INCLUDE_DIR}/Logger.hpp
    ${INCLUDE_DIR}/MimeResource.hpp
    ${INCLUDE_DIR}/PerformanceMonitor.hpp
    ${INCLUDE_DIR}/Resources.hpp
    ${INCLUDE_DIR}/RootResource.hpp
    ${INCLUDE_DIR}/ServerOptions.hpp
)

## Set output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Bin)

## Application executable and link dependencies
add_executable(${TARGET} ${SOURCES})
set_target_properties(
    ${TARGET}
    PROPERTIES
    OUTPUT_NAME ${TARGET}
    PREFIX ""
    SUFFIX ".exe"
)


## Add link directories
target_link_directories(${TARGET} PRIVATE /usr/local/lib)

## Link Dependencies
target_link_libraries(${TARGET} httpserver microhttpd pthread)

# ------------- TESTING ------------- #

## Add testing support
project("utopia-server-tests" CXX)
set(TESTS "utopia-server-tests")

## Include directories
include_directories(${TESTS} ${CMAKE_CURRENT_BINARY_DIR}/Includes)
include_directories(${TESTS} ${CMAKE_CURRENT_BINARY_DIR}/Tests)

## Source directories
set(SOURCE_DIR Sources)
set(TESTS_DIR Tests)

## Add CXX sources
set(TEST_SOURCES
    # CXX sources
    ${TESTS_DIR}/TestSuite.cpp
    ${TESTS_DIR}/TestServerOptions.cpp
    ${SOURCE_DIR}/Authorization.cpp
    ${SOURCE_DIR}/Logger.cpp
    ${SOURCE_DIR}/PerformanceMonitor.cpp
    ${SOURCE_DIR}/ServerOptions.cpp
    # CXX includes
    ${TESTS_DIR}/TestSuite.hpp
    ${TESTS_DIR}/TestServerOptions.hpp
    ${INCLUDE_DIR}/Authorization.hpp
    ${INCLUDE_DIR}/HelloResource.hpp
    ${INCLUDE_DIR}/Logger.hpp
    ${INCLUDE_DIR}/PerformanceMonitor.hpp
    ${INCLUDE_DIR}/Resources.hpp
    ${INCLUDE_DIR}/RootResource.hpp
    ${INCLUDE_DIR}/ServerOptions.hpp
)

## Test executable and link dependencies
add_executable(${TESTS} ${TEST_SOURCES}) 
set_target_properties(
    ${TESTS}
    PROPERTIES
    OUTPUT_NAME ${TESTS}
    PREFIX ""
    SUFFIX ".exe"
)

## Link Dependencies
target_link_libraries(${TESTS} httpserver microhttpd)
