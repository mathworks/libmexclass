cmake_minimum_required(VERSION 3.0.0)

# CMake policy CM0074 must be set explicitly by any client project 
# that wants to use find_package with a <PACKAGE>_ROOT variable. 
# Therefore, we set this policy to enable support for the Matlab_ROOT
# flag with find_package(Matlab)
cmake_policy(SET CMP0074 NEW)

# Project metadata.
set(LIBMEXCLASS_PROJECT_NAME libmexclass)
project(${LIBMEXCLASS_PROJECT_NAME} VERSION 0.1.0)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# Find MATLAB.
find_package(Matlab REQUIRED)

# ###########
# libmexclass
# ###########

# Sources.
set(LIBMEXCLASS_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source)
set(LIBMEXCLASS_SOURCES
    ${LIBMEXCLASS_SOURCE_DIR}/libmexclass/action/TypeFactory.cpp
    ${LIBMEXCLASS_SOURCE_DIR}/libmexclass/action/Unsupported.cpp
    ${LIBMEXCLASS_SOURCE_DIR}/libmexclass/action/Create.cpp
    ${LIBMEXCLASS_SOURCE_DIR}/libmexclass/action/Destroy.cpp
    ${LIBMEXCLASS_SOURCE_DIR}/libmexclass/action/MethodCall.cpp
    ${LIBMEXCLASS_SOURCE_DIR}/libmexclass/proxy/Proxy.cpp
    ${LIBMEXCLASS_SOURCE_DIR}/libmexclass/proxy/ProxyManager.cpp
)

# Create libmexclass shared library target.
set(LIBMEXCLASS_LIBRARY_NAME mexclass)
add_library(${LIBMEXCLASS_LIBRARY_NAME} SHARED ${LIBMEXCLASS_SOURCES})

# Set compiler features to require C++17.
target_compile_features(${LIBMEXCLASS_LIBRARY_NAME} PRIVATE cxx_std_17)

# Include directories (i.e. header files).
set(LIBMEXCLASS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source/include)
message(STATUS "LIBMEXCLASS_INCLUDE_DIR = ${LIBMEXCLASS_INCLUDE_DIR}")
target_include_directories(${LIBMEXCLASS_LIBRARY_NAME} PRIVATE ${Matlab_INCLUDE_DIRS})
target_include_directories(${LIBMEXCLASS_LIBRARY_NAME} PRIVATE ${LIBMEXCLASS_INCLUDE_DIR})

# Link against MEX shared library.
target_link_libraries(${LIBMEXCLASS_LIBRARY_NAME} PRIVATE ${Matlab_MEX_LIBRARY})
# Link against MATLAB Data Array shared library.
target_link_libraries(${LIBMEXCLASS_LIBRARY_NAME} PRIVATE ${Matlab_DATAARRAY_LIBRARY})

# TODO: Use Imported targets. This requires a newer version of CMake.
# target_link_libraries(${LIBMEXCLASS_LIBRARY_NAME} PRIVATE Matlab::mex)
# target_link_libraries(${LIBMEXCLASS_LIBRARY_NAME} PRIVATE Matlab::MatlabDataArray)

# #################
# libmexclassclient
# #################

macro(libmexclass_add_client_library)
    # TODO: Add required argument logic.
    set(options)
    set(oneValueArgs NAME)
    set(multiValueArgs SOURCES INCLUDE_DIRS)
    cmake_parse_arguments(LIBMEXCLASS_CLIENT_LIB "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    add_library(${LIBMEXCLASS_CLIENT_LIB_NAME} SHARED ${LIBMEXCLASS_CLIENT_LIB_SOURCES})
    target_include_directories(${LIBMEXCLASS_CLIENT_LIB_NAME} PRIVATE ${LIBMEXCLASS_CLIENT_LIB_INCLUDE_DIRS})

    target_include_directories(${LIBMEXCLASS_CLIENT_LIB_NAME} PRIVATE ${Matlab_INCLUDE_DIRS})
    target_include_directories(${LIBMEXCLASS_CLIENT_LIB_NAME} PRIVATE ${LIBMEXCLASS_INCLUDE_DIR})

    # Link against libmexclass shared library.
    target_link_libraries(${LIBMEXCLASS_CLIENT_LIB_NAME} PRIVATE mexclass)
    # TODO: Should we link against custom link libraries here explicitly?
endmacro()

# ###########
# MEX gateway
# ###########

macro(libmexclass_add_mex_gateway)
    # TODO: Add required argument logic.
    set(options)
    set(oneValueArgs NAME CLIENT_LIBRARY)
    set(multiValueArgs SOURCES)
    cmake_parse_arguments(LIBMEXCLASS_MEX_GATEWAY "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    matlab_add_mex(NAME ${LIBMEXCLASS_MEX_GATEWAY_NAME}
                   SRC ${LIBMEXCLASS_MEX_GATEWAY_SOURCES}
                   LINK_TO libmexclass
                           ${LIBMEXCLASS_MEX_GATEWAY_CLIENT_LIB)
    # Set compiler features to require C++17.
    target_compile_features(${LIBMEXCLASS_MEX_GATEWAY_NAME} PRIVATE cxx_std_17)
    # Include directories (i.e. header files).
    # TODO: Consider ways of automatically using target properties to add headers to target_include_directories for client_lib.
    # TODO: Set target_include_directories to include LIBMEXCLASS headers and client proxy lib headers.
endmacro()
