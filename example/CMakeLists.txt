cmake_minimum_required(VERSION 3.0.0)

set(CLIENT_PROJECT_NAME client)
set(CLIENT_EXECUTABLE_NAME client)

project(${CLIENT_PROJECT_NAME} VERSION 0.1.0)

set(CUSTOM_PROXY_FACTORY_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# TODO: Consider renaming this target to disambguate from the imported libmexclass target.
set(LIBMEXCLASS_EXTERNAL_PROJECT_TARGET_NAME libmexclass)
# TODO: Change to Git repository URL in production.
set(LIBMEXCLASS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../libmexclass/cpp)

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
    # Pass in the client's CUSTOM_PROXY_FACTORY_DIR.
    CMAKE_ARGS -D CUSTOM_PROXY_FACTORY_DIR=${CUSTOM_PROXY_FACTORY_DIR}
               -D CMAKE_CXX_COMPILER_LAUNCHER=ccache
    # TODO: What should the install step do?
    INSTALL_COMMAND ""
)

# Set the instllation directory for libmexclass.
ExternalProject_Get_Property(${LIBMEXCLASS_EXTERNAL_PROJECT_TARGET_NAME} BINARY_DIR)
# TODO: Only copy libmexclass.so and gateway.mexa64
install(DIRECTORY ${BINARY_DIR} DESTINATION libmexclass)
