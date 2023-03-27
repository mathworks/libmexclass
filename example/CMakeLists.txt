cmake_minimum_required(VERSION 3.0.0)

set(CLIENT_PROJECT_NAME client)
set(CLIENT_EXECUTABLE_NAME client)

project(${CLIENT_PROJECT_NAME} VERSION 0.1.0)

# ####################
# Client Configuration
# ####################

# Note: Clients must call find_package(Matlab REQUIRED) to ensure
#       that the appropriate MATLAB-related CMake variables
#       are available for use by libmexclass.
find_package(Matlab REQUIRED)

# Add libmexclass using FetchContent.
include(FetchContent)
set(LIBMEXCLASS_FETCH_CONTENT_NAME libmexclass)
# GIT_TAG for libmexclass source from Git.
# Note: Clients who don't want to depend on main (which may have breaking changes)
#       can specify a specific commit using the LIBMEXCLASS_GIT_TAG argument with
#       the cmake command. By default, source from the main branch will be used.
set(LIBMEXCLASS_GIT_TAG main CACHE STRING "")
FetchContent_Declare(
    ${LIBMEXCLASS_FETCH_CONTENT_NAME}
    # TODO: Consider using SSH URL for the Git Repository when CI works without permission issues.
    # GIT_REPOSITORY git@github.com:mathworks/libmexclass.git
    GIT_REPOSITORY https://github.com/mathworks/libmexclass.git
    GIT_TAG ${LIBMEXCLASS_GIT_TAG}
    # Source directory for libmexclass.
    SOURCE_SUBDIR libmexclass/cpp
)
FetchContent_MakeAvailable(
    ${LIBMEXCLASS_FETCH_CONTENT_NAME}
)

set(LIBMEXCLASS_CLIENT_LIBRARY_NAME "example")
set(LIBMEXCLASS_CLIENT_LIBRARY_INCLUDE_DIRS ${CMAKE_SOURCE_DIR})
set(LIBMEXCLASS_CLIENT_LIBRARY_SOURCES
    ${CMAKE_SOURCE_DIR}/CarProxyFactory.cpp
    ${CMAKE_SOURCE_DIR}/Car.cpp
    ${CMAKE_SOURCE_DIR}/proxy/Car.cpp
)

libmexclass_add_client_library(
    NAME ${LIBMEXCLASS_CLIENT_LIBRARY_NAME}
    SOURCES ${LIBMEXCLASS_CLIENT_LIBRARY_SOURCES}
    INCLUDE_DIRS ${LIBMEXCLASS_CLIENT_LIBRARY_INCLUDE_DIRS}
)
target_compile_features(${LIBMEXCLASS_CLIENT_LIBRARY_NAME} PRIVATE cxx_std_17)

set(LIBMEXCLASS_CLIENT_MEX_GATEWAY_NAME "gateway")
set(LIBMEXCLASS_CLIENT_MEX_GATEWAY_SOURCES ${CMAKE_SOURCE_DIR}/mex/gateway.cpp)

libmexclass_add_mex_gateway(
    NAME ${LIBMEXCLASS_CLIENT_MEX_GATEWAY_NAME}
    CLIENT_LIBRARY ${LIBMEXCLASS_CLIENT_LIBRARY_NAME}
    SOURCES ${LIBMEXCLASS_CLIENT_MEX_GATEWAY_SOURCES}
)
