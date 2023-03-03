cmake_minimum_required(VERSION 3.0.0)

set(CLIENT_PROJECT_NAME client)
set(CLIENT_EXECUTABLE_NAME client)

project(${CLIENT_PROJECT_NAME} VERSION 0.1.0)

# TODO: Issue #25: Consider renaming this target to disambguate from the imported libmexclass target.
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
# Clients must use the libmexclass/cpp/libmexclassInstall.cmake to complete the installation steps and package the binaries.
set(LIBMEXCLASS_INSTALL_STEPS_FILE ${LIBMEXCLASS_DIR}/libmexclassInstall.cmake)
# Clients must specify ${CMAKE_INSTALL_DIR} to which the packaged install will be placed.
set(CMAKE_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/libmexclass)
ExternalProject_Add(	
    # Name of the external project target.
    ${LIBMEXCLASS_EXTERNAL_PROJECT_TARGET_NAME}
    # Don't download anything. Instead, use the local libmexclass sources.
    # TODO: This should be removed when using the Git repository URL.
    DOWNLOAD_COMMAND ""
    # Source directory for libmexclass.
    # TODO: This should be removed when using the Git repository URL.
    SOURCE_DIR ${LIBMEXCLASS_DIR}
    # Clients must supply the following information:
    #
    # 1. CUSTOM_PROXY_FACTORY_INCLUDE_DIR
    # 2. CUSTOM_PROXY_FACTORY_SOURCES
    # 3. CUSTOM_PROXY_SOURCES
    #
    CMAKE_CACHE_ARGS "-D CUSTOM_PROXY_FACTORY_INCLUDE_DIR:STRING=${CUSTOM_PROXY_FACTORY_INCLUDE_DIR}"
                     "-D CUSTOM_PROXY_FACTORY_SOURCES:STRING=${CUSTOM_PROXY_FACTORY_SOURCES}"
                     "-D CUSTOM_PROXY_SOURCES:STRING=${CUSTOM_PROXY_SOURCES}"
	# Execute LIBMEXCLASS_INSTALL_STEPS_FILE as a script.    
	INSTALL_COMMAND ${CMAKE_COMMAND} -D CMAKE_INSTALL_DIR=${CMAKE_INSTALL_DIR} -P ${LIBMEXCLASS_INSTALL_STEPS_FILE}
)

install(CODE "MESSAGE(\"Completed install step for ${CLIENT_PROJECT_NAME}.\")")