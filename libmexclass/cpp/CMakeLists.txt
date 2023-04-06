cmake_minimum_required(VERSION 3.0.0)

# CMake policy CM0074 must be set explicitly by any client project 
# that wants to use find_package with a <PACKAGE>_ROOT variable. 
# Therefore, we set this policy to enable support for the Matlab_ROOT
# flag with find_package(Matlab)
cmake_policy(SET CMP0074 NEW)

# Project metadata.
set(LIBMEXCLASS_PROJECT_NAME libmexclass)
project(${LIBMEXCLASS_PROJECT_NAME} VERSION 0.1.0)

# ################
# Helper Functions
# ################

# Install the runtime libraries of an IMPORTED target.
function(install_imported_target)
    # TODO: Add required argument logic.
    set(options)
    set(oneValueArgs NAME DESTINATION)
    set(multiValueArgs)
    cmake_parse_arguments(LIBMEXCLASS_INSTALL_IMPORTED_TARGET "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
    get_target_property(RUNTIME_LIBRARY ${LIBMEXCLASS_INSTALL_IMPORTED_TARGET_NAME} IMPORTED_LOCATION)
    get_filename_component(RUNTIME_LIBRARY_DIRECTORY ${RUNTIME_LIBRARY} DIRECTORY)
    get_filename_component(RUNTIME_LIBRARY_FILENAME ${RUNTIME_LIBRARY} NAME_WE)
    set(TEMP_RUNTIME_LIBRARY_INSTALL_DIRECTORY "${RUNTIME_LIBRARY_FILENAME}_temp")
    file(COPY ${RUNTIME_LIBRARY} DESTINATION ${TEMP_RUNTIME_LIBRARY_INSTALL_DIRECTORY} FOLLOW_SYMLINK_CHAIN)
    message(STATUS "TEMP_RUNTIME_LIBRARY_INSTALL_DIRECTORY = ${TEMP_RUNTIME_LIBRARY_INSTALL_DIRECTORY}")
    install(DIRECTORY ${TEMP_RUNTIME_LIBRARY_INSTALL_DIRECTORY}/ DESTINATION ${LIBMEXCLASS_INSTALL_IMPORTED_TARGET_DESTINATION})
endfunction()

# Set the given target's RPATH on Linux and macOS.
function(target_set_rpath_relocatable)
    # TODO: Add required argument logic.
    set(options)
    set(oneValueArgs NAME)
    set(multiValueArgs)
    cmake_parse_arguments(LIBMEXCLASS_TARGET_SET_RPATH "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
    
    if(APPLE)
        set_target_properties(${LIBMEXCLASS_TARGET_SET_RPATH_NAME} PROPERTIES INSTALL_RPATH "@loader_path")
    else()
        set_target_properties(${LIBMEXCLASS_TARGET_SET_RPATH_NAME} PROPERTIES INSTALL_RPATH "$ORIGIN")
    endif()
endfunction()

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

target_set_rpath_relocatable(NAME ${LIBMEXCLASS_LIBRARY_NAME})

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
    set(multiValueArgs SOURCES INCLUDE_DIRS LINK_LIBRARIES)
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
    
    define_property(
        TARGET
        PROPERTY LIBMEXCLASS_CLIENT_PROXY_LIBRARY_LINK_LIBRARIES
        BRIEF_DOCS "Additional link libraries for client Proxy library"
        FULL_DOCS "Target names of additional shared libraries to link against the libmexclass client Proxy library."
    )

    if(DEFINED LIBMEXCLASS_CLIENT_PROXY_LIBRARY_LINK_LIBRARIES)
        foreach(LINK_LIBRARY ${LIBMEXCLASS_CLIENT_PROXY_LIBRARY_LINK_LIBRARIES})
            get_target_property(TARGET_INCLUDE_DIRECTORIES ${LINK_LIBRARY} INTERFACE_INCLUDE_DIRECTORIES)
            target_include_directories(${LIBMEXCLASS_CLIENT_PROXY_LIBRARY_NAME} PRIVATE ${TARGET_INCLUDE_DIRECTORIES})
            target_link_libraries(${LIBMEXCLASS_CLIENT_PROXY_LIBRARY_NAME} PRIVATE ${LINK_LIBRARY})
        endforeach()


        set_property(
            TARGET ${LIBMEXCLASS_CLIENT_PROXY_LIBRARY_NAME}
            PROPERTY LIBMEXCLASS_CLIENT_PROXY_LIBRARY_LINK_LIBRARIES ${LIBMEXCLASS_CLIENT_PROXY_LIBRARY_LINK_LIBRARIES} 
        )
    endif()

    target_set_rpath_relocatable(NAME ${LIBMEXCLASS_CLIENT_PROXY_LIBRARY_NAME})
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

    target_set_rpath_relocatable(NAME ${LIBMEXCLASS_CLIENT_MEX_GATEWAY_NAME})
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

    get_target_property(LINK_LIBRARIES ${LIBMEXCLASS_CLIENT_INSTALL_CLIENT_PROXY_LIBRARY_NAME} LIBMEXCLASS_CLIENT_PROXY_LIBRARY_LINK_LIBRARIES)
    if(DEFINED ${LINK_LIBRARIES})
        foreach(LINK_LIBRARY ${LINK_LIBRARIES})
            get_target_property(LINK_LIBRARY_IS_IMPORTED ${LINK_LIBRARY} IMPORTED)
            message("LINK_LIBRARY_IS_IMPORTED = ${LINK_LIBRARY_IS_IMPORTED}")
            if(${LINK_LIBRARY_IS_IMPORTED})
                message(STATUS "${LINK_LIBRARY} is an IMPORTED target.")
                install_imported_target(NAME ${LINK_LIBRARY} DESTINATION +libmexclass/+proxy)
            else()
                install(TARGETS ${LINK_LIBRARY} DESTINATION +libmexclass/+proxy)
            endif()
        endforeach()
    endif()
endmacro()
