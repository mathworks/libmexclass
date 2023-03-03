cmake_minimum_required(VERSION 3.0.0)

set(CLIENT_PROJECT_NAME client)
set(CLIENT_EXECUTABLE_NAME client)

project(${CLIENT_PROJECT_NAME} VERSION 0.1.0)

# TODO: Consider renaming this target to disambguate from the imported libmexclass target.
set(LIBMEXCLASS_EXTERNAL_PROJECT_TARGET_NAME libmexclass)
# TODO: Change to Git repository URL in production.
set(LIBMEXCLASS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../libmexclass/cpp)

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

# Add libmexclass as an external project.
include(ExternalProject)
ExternalProject_Add(
    # Name of the external project target.
    ${LIBMEXCLASS_EXTERNAL_PROJECT_TARGET_NAME}
    # Don't download anything. Instead, use the local libmexclass sources.
    # TODO: This should be removed when using the Git repository URL.
    DOWNLOAD_COMMAND ""
    # Source directory for libmexclass.
    # TODO: This should be removed when using the Git repository URL.
    SOURCE_DIR ${LIBMEXCLASS_DIR}
    # Client's must supply the following information:
    #
    # 1. CUSTOM_PROXY_FACTORY_INCLUDE_DIR
    # 2. CUSTOM_PROXY_FACTORY_SOURCES
    # 3. CUSTOM_PROXY_SOURCES
    #
    CMAKE_CACHE_ARGS "-D CUSTOM_PROXY_FACTORY_INCLUDE_DIR:STRING=${CUSTOM_PROXY_FACTORY_INCLUDE_DIR}"
                     "-D CUSTOM_PROXY_FACTORY_SOURCES:STRING=${CUSTOM_PROXY_FACTORY_SOURCES}"
                     "-D CUSTOM_PROXY_SOURCES:STRING=${CUSTOM_PROXY_SOURCES}"
    # TODO: What should the install step do?
    INSTALL_COMMAND ""
)

# Get the source directory for libmexclass.
ExternalProject_Get_Property(${LIBMEXCLASS_EXTERNAL_PROJECT_TARGET_NAME} SOURCE_DIR)
# Get the instllation directory for libmexclass.
ExternalProject_Get_Property(${LIBMEXCLASS_EXTERNAL_PROJECT_TARGET_NAME} BINARY_DIR)

set(LIBMEXCLASS_MATLAB_SOURCES ${SOURCE_DIR}/../matlab/)

# TODO: Only copy libmexclass.so and gateway.mexa64
install(DIRECTORY ${BINARY_DIR}/ DESTINATION libmexclass)
install(DIRECTORY ${LIBMEXCLASS_MATLAB_SOURCES} DESTINATION libmexclass)
