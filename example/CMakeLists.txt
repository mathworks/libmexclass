# ########################################
# libmexclass Client Project Configuration
# ########################################

cmake_minimum_required(VERSION 3.0.0)

set(CLIENT_PROJECT_NAME example)
project(${CLIENT_PROJECT_NAME} VERSION 0.1.0)


set(MATLAB_ADDITIONAL_VERSIONS
    "R2023b=23.2")
set(Matlab_ROOT_DIR "C:/Program Files/MATLAB/R2023b")
find_package(Matlab REQUIRED)
message(STATUS "Matlab_VERSION_STRING = ${Matlab_VERSION_STRING}")
set(Matlab_VERSION_STRING "23.2")
message(STATUS "Matlab_VERSION_STRING (after set) = ${Matlab_VERSION_STRING}")


# ######################################
# libmexclass FetchContent Configuration
# ######################################

# Add libmexclass to the client project using FetchContent.

set(LIBMEXCLASS_FETCH_CONTENT_NAME libmexclass)
# TODO: Consider using SSH URL for the Git Repository when CI works without permission issues.
# GIT_REPOSITORY git@github.com:mathworks/libmexclass.git
set(LIBMEXCLASS_FETCH_CONTENT_GIT_REPOSITORY "https://github.com/mathworks/libmexclass.git")
# GIT_TAG for libmexclass source from Git.
# Note: Clients who don't want to depend on main (which may have breaking changes)
#       can specify a specific Git commit using the LIBMEXCLASS_GIT_TAG argument.
#       By default, the main branch will be used.
set(LIBMEXCLASS_FETCH_CONTENT_GIT_TAG main CACHE STRING "")
# Source directory for libmexclass.
set(LIBMEXCLASS_FETCH_CONTENT_SOURCE_SUBDIR "libmexclass/cpp")

include(FetchContent)
FetchContent_Declare(
    ${LIBMEXCLASS_FETCH_CONTENT_NAME}
    GIT_REPOSITORY ${LIBMEXCLASS_FETCH_CONTENT_GIT_REPOSITORY}
    GIT_TAG ${LIBMEXCLASS_FETCH_CONTENT_GIT_TAG}
    SOURCE_SUBDIR ${LIBMEXCLASS_FETCH_CONTENT_SOURCE_SUBDIR}
)
FetchContent_MakeAvailable(
    ${LIBMEXCLASS_FETCH_CONTENT_NAME}
)

# ################################
# libmexclass Client Proxy Library
# ################################

# Set C++ sources and headers.
set(LIBMEXCLASS_CLIENT_PROXY_LIBRARY_NAME "carproxy")
set(LIBMEXCLASS_CLIENT_PROXY_LIBRARY_INCLUDE_DIRS ${CMAKE_SOURCE_DIR})
set(LIBMEXCLASS_CLIENT_PROXY_LIBRARY_SOURCES
    ${CMAKE_SOURCE_DIR}/CarProxyFactory.cpp
    ${CMAKE_SOURCE_DIR}/Car.cpp
    ${CMAKE_SOURCE_DIR}/proxy/Car.cpp
)

# Create the libmexclass client Proxy library target.
#
# NOTE: Additional libraries to link the client
#       Proxy library against can be specified
#       using the LINK_LIBRARIES argument to
#       libmexclass_client_add_proxy_library.

libmexclass_client_add_proxy_library(
    NAME ${LIBMEXCLASS_CLIENT_PROXY_LIBRARY_NAME}
    SOURCES ${LIBMEXCLASS_CLIENT_PROXY_LIBRARY_SOURCES}
    INCLUDE_DIRS ${LIBMEXCLASS_CLIENT_PROXY_LIBRARY_INCLUDE_DIRS}
)

# NOTE: Clients can modify the client Proxy library target
#       as needed after it has been created using normal CMake
#       commands.
#
#       For example:
# 
#       set_target_properties(${LIBMEXCLASS_CLIENT_PROXY_LIBRARY_NAME}
#                             PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "example")
#
#       get_target_property(CLIENT_PROXY_LIBRARY_INCLUDE_DIRS
#                           ${LIBMEXCLASS_CLIENT_PROXY_LIBRARY_NAME} INCLUDE_DIRECTORIES)

# Use C++17 for the client Proxy library.
target_compile_features(${LIBMEXCLASS_CLIENT_PROXY_LIBRARY_NAME} PRIVATE cxx_std_17)

# ##############################
# libmexclass Client MEX Gateway
# ##############################

# Create the libmexclass client MEX gateway target.

set(LIBMEXCLASS_CLIENT_MEX_GATEWAY_NAME "gateway")
set(LIBMEXCLASS_CLIENT_MEX_GATEWAY_SOURCES ${CMAKE_SOURCE_DIR}/mex/gateway.cpp)

libmexclass_client_add_mex_gateway(
    NAME ${LIBMEXCLASS_CLIENT_MEX_GATEWAY_NAME}
    CLIENT_PROXY_LIBRARY_NAME ${LIBMEXCLASS_CLIENT_PROXY_LIBRARY_NAME}
    SOURCES ${LIBMEXCLASS_CLIENT_MEX_GATEWAY_SOURCES}
)

# ###############################
# libmexclass Client Installation
# ###############################

# Install the following files to the specified ${DESTINATION} (relative to ${CMAKE_INSTALL_PREFIX}):
#
# (1) libmexclass shared library (libmexclass.so)
# (2) libmexclass client MEX gateway (gateway.mexa64)
# (3) libmexclass client Proxy library (libcarproxy.so)
# (4) Additional link libraries for libmexclass client Proxy library
#
#     NOTE: This only applies to libraries specified using the LINK_LIBRARIES argument
#           to libmexclass_client_add_proxy_library.
#     NOTE: Link libraries added via explicit calls to target_link_libraries
#           must be installed to ${CMAKE_INSTALL_PREFIX}/${DESTINATION}/+libmexclass/+proxy manually.
# 
# NOTE: Files will be installed to: ${CMAKE_INSTALL_PREFIX}/${DESTINATION}/+libmexclass/+proxy
# NOTE: The ${CMAKE_INSTALL_PREFIX} must be added to the MATLAB Path to use the client libmexclass code.
#

libmexclass_client_install(
    CLIENT_PROXY_LIBRARY_NAME ${LIBMEXCLASS_CLIENT_PROXY_LIBRARY_NAME}
    CLIENT_MEX_GATEWAY_NAME ${LIBMEXCLASS_CLIENT_MEX_GATEWAY_NAME}
    DESTINATION "."
)
