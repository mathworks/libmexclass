cmake_minimum_required(VERSION 3.0.0)

set(CLIENT_PROJECT_NAME client)
set(CLIENT_EXECUTABLE_NAME client)

project(${CLIENT_PROJECT_NAME} VERSION 0.1.0)

# ####################
# Client Configuration
# ####################

set(CUSTOM_PROXY_FACTORY_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(CUSTOM_PROXY_FACTORY_HEADER_FILENAME CarProxyFactory.h)
set(CUSTOM_PROXY_FACTORY_CLASS_NAME CarProxyFactory)

set(CUSTOM_PROXY_FACTORY_SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(CUSTOM_PROXY_FACTORY_SOURCES
    ${CUSTOM_PROXY_FACTORY_SOURCES_DIR}/CarProxyFactory.cpp
)

set(CUSTOM_PROXY_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/proxy)

set(CUSTOM_PROXY_SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(CUSTOM_PROXY_SOURCES
    ${CUSTOM_PROXY_SOURCES_DIR}/Car.cpp
    ${CUSTOM_PROXY_SOURCES_DIR}/proxy/Car.cpp
)

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
FetchContent_MakeAvailable(${LIBMEXCLASS_FETCH_CONTENT_NAME})
