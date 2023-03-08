cmake_minimum_required(VERSION 3.0.0)

set(CLIENT_PROJECT_NAME client)
set(CLIENT_EXECUTABLE_NAME client)

project(${CLIENT_PROJECT_NAME} VERSION 0.1.0)

# TODO: Consider renaming this target to disambguate from the imported libmexclass target.
set(LIBMEXCLASS_EXTERNAL_PROJECT_TARGET_NAME libmexclass)

# ####################
# Client Configuration
# ####################

set(CUSTOM_PROXY_FACTORY_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(CUSTOM_PROXY_FACTORY_SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(CUSTOM_PROXY_FACTORY_SOURCES
    ${CUSTOM_PROXY_FACTORY_SOURCES_DIR}/CustomProxyFactory.cpp
)

set(CUSTOM_PROXY_SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(CUSTOM_PROXY_SOURCES
    ${CUSTOM_PROXY_SOURCES_DIR}/Car.cpp
    ${CUSTOM_PROXY_SOURCES_DIR}/proxy/Car.cpp
)

set(CUSTOM_PROXY_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/proxy)

# Add libmexclass as an external project.
include(ExternalProject)
# GIT_TAG for libmexclass source from Git.
# Note: Clients who don't want to depend on main (which may have breaking changes) can specify a specific commit using the LIBMEXCLASS_GIT_TAG argument with cmake command. By default source from the main branch will be used.
set(LIBMEXCLASS_GIT_TAG main CACHE STRING "")
message(STATUS "LIBMEXCLASS_GIT_TAG: ${LIBMEXCLASS_GIT_TAG}")
ExternalProject_Add(
    # Name of the external project target.
    ${LIBMEXCLASS_EXTERNAL_PROJECT_TARGET_NAME}
    # TODO: Consider using SSH URL for the Git Repository when CI works without permission issues.
    # GIT_REPOSITORY git@github.com:mathworks/libmexclass.git
    GIT_REPOSITORY https://github.com/mathworks/libmexclass.git
    GIT_TAG ${LIBMEXCLASS_GIT_TAG}
    # Source directory for libmexclass.
    SOURCE_SUBDIR libmexclass/cpp
    # Clients must supply the following information:
    #
    # 1. CUSTOM_PROXY_FACTORY_INCLUDE_DIR
    # 2. CUSTOM_PROXY_FACTORY_SOURCES
    # 3. CUSTOM_PROXY_SOURCES
    #
    CMAKE_CACHE_ARGS "-D CUSTOM_PROXY_FACTORY_INCLUDE_DIR:STRING=${CUSTOM_PROXY_FACTORY_INCLUDE_DIR}"
                     "-D CUSTOM_PROXY_FACTORY_SOURCES:STRING=${CUSTOM_PROXY_FACTORY_SOURCES}"
                     "-D CUSTOM_PROXY_INCLUDE_DIR:STRING=${CUSTOM_PROXY_INCLUDE_DIR}"
                     "-D CUSTOM_PROXY_SOURCES:STRING=${CUSTOM_PROXY_SOURCES}"
    # Clients must use the below command for installing the external project.
    # "${CMAKE_COMMAND} --install ." will also work for CMake 3.15 onwards.
    INSTALL_COMMAND ${CMAKE_COMMAND} --build . --target install
)

# Get the installation directory for libmexclass.
ExternalProject_Get_Property(${LIBMEXCLASS_EXTERNAL_PROJECT_TARGET_NAME} BINARY_DIR)

# Copy only the packaged folder +libmexclass from the installation directory.
install(DIRECTORY ${BINARY_DIR}/+libmexclass DESTINATION libmexclass)