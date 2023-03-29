cmake_minimum_required(VERSION 3.0.0)

# CMake policy CM0074 must be set explicitly by any client project 
# that wants to use find_package with a <PACKAGE>_ROOT variable. 
# Therefore, we set this policy to enable support for the Matlab_ROOT
# flag with find_package(Matlab)
cmake_policy(SET CMP0074 NEW)

# Project metadata.
set(LIBMEXCLASS_PROJECT_NAME libmexclass)
project(${LIBMEXCLASS_PROJECT_NAME} VERSION 0.1.0)

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
set_target_properties(${LIBMEXCLASS_LIBRARY_NAME} PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)

# Set compiler features to require C++17.
target_compile_features(${LIBMEXCLASS_LIBRARY_NAME} PRIVATE cxx_std_17)

# Include directories (i.e. header files).
set(LIBMEXCLASS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source/include)
target_include_directories(${LIBMEXCLASS_LIBRARY_NAME} PRIVATE ${Matlab_INCLUDE_DIRS})
target_include_directories(${LIBMEXCLASS_LIBRARY_NAME} PRIVATE ${LIBMEXCLASS_INCLUDE_DIR})

# Link against MEX shared library.
target_link_libraries(${LIBMEXCLASS_LIBRARY_NAME} PRIVATE ${Matlab_MEX_LIBRARY})
# Link against MATLAB Data Array shared library.
target_link_libraries(${LIBMEXCLASS_LIBRARY_NAME} PRIVATE ${Matlab_DATAARRAY_LIBRARY})

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	set_target_properties(${LIBMEXCLASS_LIBRARY_NAME} PROPERTIES INSTALL_RPATH @loader_path)
	message(STATUS "Inside Darwin.")
else()
	set_target_properties(${LIBMEXCLASS_LIBRARY_NAME} PROPERTIES INSTALL_RPATH $ORIGIN)
endif()

message(STATUS "INSTALL_RPATH: ${INSTALL_RPATH}")

# TODO: Use Imported targets. This requires a newer version of CMake.
# target_link_libraries(${LIBMEXCLASS_LIBRARY_NAME} PRIVATE Matlab::mex)
# target_link_libraries(${LIBMEXCLASS_LIBRARY_NAME} PRIVATE Matlab::MatlabDataArray)

# #################
# libmexclassmatlab
# #################

add_custom_target(mexclassmatlab)
define_property(
    TARGET
    PROPERTY MATLAB_SOURCES
    BRIEF_DOCS "Location of libmexclass MATLAB sources"
    FULL_DOCS "The location of the libmexclass MATLAB sources (i.e. the location of the +libmexclass directory)."
)
set_property(
    TARGET mexclassmatlab
    PROPERTY MATLAB_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/../matlab/+libmexclass"
)

# #################
# libmexclassclient
# #################

macro(libmexclass_client_add_proxy_library)
    # TODO: Add required argument logic.
    set(options)
    set(oneValueArgs NAME)
    set(multiValueArgs SOURCES INCLUDE_DIRS)
    cmake_parse_arguments(LIBMEXCLASS_CLIENT_PROXY_LIBRARY "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    find_package(Matlab REQUIRED)

    add_library(${LIBMEXCLASS_CLIENT_PROXY_LIBRARY_NAME} SHARED ${LIBMEXCLASS_CLIENT_PROXY_LIBRARY_SOURCES})
    set_target_properties(${LIBMEXCLASS_CLIENT_PROXY_LIBRARY_NAME} PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)
    target_include_directories(${LIBMEXCLASS_CLIENT_PROXY_LIBRARY_NAME} PRIVATE ${LIBMEXCLASS_CLIENT_PROXY_LIBRARY_INCLUDE_DIRS})

    get_target_property(LIBMEXCLASS_INCLUDE_DIRS mexclass INCLUDE_DIRECTORIES)

    target_include_directories(${LIBMEXCLASS_CLIENT_PROXY_LIBRARY_NAME} PRIVATE ${Matlab_INCLUDE_DIRS})
    target_include_directories(${LIBMEXCLASS_CLIENT_PROXY_LIBRARY_NAME} PRIVATE ${LIBMEXCLASS_INCLUDE_DIRS})

    # Link against libmexclass shared library.
    target_link_libraries(${LIBMEXCLASS_CLIENT_PROXY_LIBRARY_NAME} PRIVATE mexclass)
    # Link against MATLAB Data Array shared library.
    target_link_libraries(${LIBMEXCLASS_CLIENT_PROXY_LIBRARY_NAME} PRIVATE ${Matlab_DATAARRAY_LIBRARY})
    # Set RPATH to $ORIGIN to make the library relocatable.
    set_target_properties(${LIBMEXCLASS_CLIENT_PROXY_LIBRARY_NAME} PROPERTIES INSTALL_RPATH $ORIGIN)
    # TODO: Should we link against custom link libraries here explicitly?
endmacro()

# ###########
# MEX gateway
# ###########

macro(libmexclass_client_add_mex_gateway)
    # TODO: Add required argument logic.
    set(options)
    set(oneValueArgs NAME CLIENT_PROXY_LIBRARY)
    set(multiValueArgs SOURCES)
    cmake_parse_arguments(LIBMEXCLASS_CLIENT_MEX_GATEWAY "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    find_package(Matlab REQUIRED)

    matlab_add_mex(NAME ${LIBMEXCLASS_CLIENT_MEX_GATEWAY_NAME}
                   SRC ${LIBMEXCLASS_CLIENT_MEX_GATEWAY_SOURCES}
                   OUTPUT_NAME "gateway"
                   LINK_TO mexclass
                           ${LIBMEXCLASS_CLIENT_MEX_GATEWAY_CLIENT_PROXY_LIBRARY})
    # Set compiler features to require C++17.
    target_compile_features(${LIBMEXCLASS_CLIENT_MEX_GATEWAY_NAME} PRIVATE cxx_std_17)
    # Include directories (i.e. header files).
    get_target_property(LIBMEXCLASS_INCLUDE_DIRS mexclass INCLUDE_DIRECTORIES)
    target_include_directories(${LIBMEXCLASS_CLIENT_MEX_GATEWAY_NAME} PRIVATE ${LIBMEXCLASS_INCLUDE_DIRS})
    # TODO: Decide whether to automatically add client library include directories.
    get_target_property(LIBMEXCLASS_CLIENT_PROXY_LIBRARY_INCLUDE_DIRS ${LIBMEXCLASS_CLIENT_MEX_GATEWAY_CLIENT_PROXY_LIBRARY} INCLUDE_DIRECTORIES)
    target_include_directories(${LIBMEXCLASS_CLIENT_MEX_GATEWAY_NAME} PRIVATE ${LIBMEXCLASS_CLIENT_PROXY_LIBRARY_INCLUDE_DIRS})
    # Set RPATH to $ORIGIN to make the library relocatable.
    set_target_properties(${LIBMEXCLASS_CLIENT_MEX_GATEWAY_NAME} PROPERTIES INSTALL_RPATH $ORIGIN)
endmacro()

# ############
# Installation
# ############

macro(libmexclass_client_install)
    set(options)
    set(oneValueArgs NAME CLIENT_PROXY_LIBRARY_NAME CLIENT_MEX_GATEWAY_NAME)
    set(multiValueArgs SOURCES)
    cmake_parse_arguments(LIBMEXCLASS_CLIENT_INSTALL "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    install(TARGETS mexclass
                    ${LIBMEXCLASS_CLIENT_INSTALL_CLIENT_PROXY_LIBRARY_NAME}
                    ${LIBMEXCLASS_CLIENT_INSTALL_CLIENT_MEX_GATEWAY_NAME}
            DESTINATION +libmexclass/+proxy)
    get_target_property(MATLAB_SOURCE_DIR mexclassmatlab MATLAB_SOURCES)
    install(DIRECTORY ${MATLAB_SOURCE_DIR} DESTINATION ".")
endmacro()
