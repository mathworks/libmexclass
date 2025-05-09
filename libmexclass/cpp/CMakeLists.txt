cmake_minimum_required(VERSION 3.6.0)

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
    if (NOT ${RUNTIME_LIBRARY})
        get_target_property(RUNTIME_LIBRARY ${LIBMEXCLASS_INSTALL_IMPORTED_TARGET_NAME} LOCATION)
    endif()
    get_filename_component(RUNTIME_LIBRARY_FILENAME_NO_EXT ${RUNTIME_LIBRARY} NAME_WE)
    get_filename_component(RUNTIME_LIBRARY_DIRECTORY ${RUNTIME_LIBRARY} DIRECTORY)
    set(RUNTIME_LIBRARY_BASE_FILENAME "${RUNTIME_LIBRARY_DIRECTORY}/${RUNTIME_LIBRARY_FILENAME_NO_EXT}${CMAKE_SHARED_LIBRARY_SUFFIX}")
    # TODO: Consider alternate naming schemes for temporary directories.
    set(RUNTIME_LIBRARY_TEMP_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/libmexclass_install_runtime_libraries/${RUNTIME_LIBRARY_FILENAME_NO_EXT}")
    install(CODE "file(COPY ${RUNTIME_LIBRARY_BASE_FILENAME} DESTINATION ${RUNTIME_LIBRARY_TEMP_DIRECTORY} FOLLOW_SYMLINK_CHAIN)")
    install(DIRECTORY ${RUNTIME_LIBRARY_TEMP_DIRECTORY}/ DESTINATION ${LIBMEXCLASS_INSTALL_IMPORTED_TARGET_DESTINATION})
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

# Debugging utility function
macro(MatlabPrintVariables)
  message(STATUS "Matlab_ROOT_DIR = ${Matlab_ROOT_DIR}")
  message(STATUS "Matlab_VERSION_STRING = ${Matlab_VERSION_STRING}")
  message(STATUS "Matlab_MX_LIBRARY = ${Matlab_MX_LIBRARY}")
  message(STATUS "Matlab_MEX_LIBRARY = ${Matlab_MEX_LIBRARY}")
  message(STATUS "Matlab_ENGINE_LIBRARY = ${Matlab_ENGINE_LIBRARY}")
  message(STATUS "Matlab_DATAARRAY_LIBRARY = ${Matlab_DATAARRAY_LIBRARY}")
  message(STATUS "Matlab_HAS_CPP_API = ${Matlab_HAS_CPP_API}")
  message(STATUS "Matlab_MEX_EXTENSION = ${Matlab_MEX_EXTENSION}")
  message(STATUS "Matlab_INCLUDE_DIRS = ${Matlab_INCLUDE_DIRS}")
  message(STATUS "Matlab_EXTERN_LIBRARY_DIR = ${Matlab_EXTERN_LIBRARY_DIR}")
endmacro()

# Sets variables required by FindMatlab's matlab_add_mex function. These 
# variables are normally configured by FindMatlab (i.e. find_package(MATLAB REQUIRED)),
# but FindMatlab sporadically fails to detect the MATLAB Release Version. If so, 
# manually configure the required variables.
macro(MatlabConfigureVariables)
  if(WIN32)
    set(MATLAB_BIN_DIR "${Matlab_ROOT_DIR}/extern/lib/win64/microsoft")
    set(MATLAB_EXTERN_BIN_DIR "${Matlab_ROOT_DIR}/extern/lib/win64/microsoft")
    set(MATLAB_EXTERN_LIB_DIR "${Matlab_ROOT_DIR}/extern/lib/win64")
    set(SHARED_LIB_SUFFIX "${CMAKE_LINK_LIBRARY_SUFFIX}")
  else()
    set(SHARED_LIB_SUFFIX "${CMAKE_SHARED_LIBRARY_SUFFIX}")
    if(APPLE)
      if (${CMAKE_HOST_SYSTEM_PROCESSOR} STREQUAL "arm64")
        set(PLATFORM_FOLDER "maca64")
      else()
        set(PLATFORM_FOLDER "maci64")
      endif()
    elseif(UNIX AND NOT CYGWIN)
      set(PLATFORM_FOLDER "glnxa64")
    else()
      message(FATAL_ERROR "Unsupported platform")
    endif()
    set(MATLAB_BIN_DIR "${Matlab_ROOT_DIR}/bin/${PLATFORM_FOLDER}")
    set(MATLAB_EXTERN_BIN_DIR "${Matlab_ROOT_DIR}/extern/bin/${PLATFORM_FOLDER}")
    set(MATLAB_EXTERN_LIB_DIR "${Matlab_ROOT_DIR}/extern/lib/${PLATFORM_FOLDER}")
  endif()

  set(Matlab_HAS_CPP_API 1)
  set(Matlab_VERSION_STRING "${MATLAB_RELEASE_VERSION}")
  set(Matlab_INCLUDE_DIRS "${Matlab_ROOT_DIR}/extern/include")
  set(Matlab_ENGINE_LIBRARY "${MATLAB_EXTERN_BIN_DIR}/libMatlabEngine${SHARED_LIB_SUFFIX}")
  set(Matlab_DATAARRAY_LIBRARY "${MATLAB_BIN_DIR}/libMatlabDataArray${SHARED_LIB_SUFFIX}")
  set(Matlab_MEX_LIBRARY "${MATLAB_BIN_DIR}/libmex${SHARED_LIB_SUFFIX}")
  set(Matlab_MX_LIBRARY "${MATLAB_BIN_DIR}/libmx${SHARED_LIB_SUFFIX}")
  set(Matlab_EXTERN_LIBRARY_DIR "${MATLAB_EXTERN_LIB_DIR}")
endmacro()

# Finds MATLAB and configures the variables necessary for building libmexclass,
# client proxy libraries, and client proxy mex gateway functions.
macro(MatlabConfigure)
  find_package(Matlab REQUIRED)
  message(STATUS "Matlab_VERSION_STRING = ${Matlab_VERSION_STRING}")

  if (${Matlab_VERSION_STRING} STREQUAL "unknown")
    # Derive the MATLAB Release Version Number from VersionInfo.xml.
    # The matlab_add_mex function needs to know the MATLAB Release Version Number
    # (i.e. Matlab_VERSION_STRING) in order to properly compile MEX functions.
    set(VERSION_INFO_FILENAME "${Matlab_ROOT_DIR}/VersionInfo.xml")
    file(READ ${VERSION_INFO_FILENAME} VERSION_INFO_TEXT)
    string(REGEX MATCH "<version>([0-9]+[.])+[0-9]+</version>" VERSION_XML_NODE ${VERSION_INFO_TEXT})
    string(REGEX MATCH "([0-9]+[.])+[0-9]+" LONG_VERSION_STRING ${VERSION_XML_NODE})
    string(REGEX MATCH "^[0-9]+[.][0-9]+" MATLAB_RELEASE_VERSION ${LONG_VERSION_STRING})
    message(STATUS "MATLAB_RELEASE_VERSION = ${MATLAB_RELEASE_VERSION}")
    MatlabConfigureVariables()
  endif()
endmacro()

# Find MATLAB.
MatlabConfigure()

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
    ${LIBMEXCLASS_SOURCE_DIR}/libmexclass/error/Error.cpp
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

    MatlabConfigure()

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
    # Link against MEX shared library.
    target_link_libraries(${LIBMEXCLASS_CLIENT_PROXY_LIBRARY_NAME} PRIVATE ${Matlab_MEX_LIBRARY})

    
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
    set(oneValueArgs NAME CLIENT_PROXY_LIBRARY_NAME)
    set(multiValueArgs SOURCES)
    cmake_parse_arguments(LIBMEXCLASS_CLIENT_MEX_GATEWAY "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

     MatlabConfigure()

    # By default matlab_add_mex automatically links the output MEX function
    # against all MEX-related libraries.
    #
    # These include: 
    #  - libmx
    #  - libmex
    #  - libMatlabDataArray
    #  - libMatlabEngine
    #
    # However, libMatlabEngine is only required for standalone C++ programs 
    # that utilize the MATLAB Engine.
    #
    # Avoid linking against libMatlabEngine by supplying the
    #  NO_IMPLICIT_LINK_TO_MATLAB_LIBRARIES flag and manually passing
    # the required mex-related libraries as arguments for the LINK_TO parameter.
    #
    matlab_add_mex(NAME ${LIBMEXCLASS_CLIENT_MEX_GATEWAY_NAME}
                   SRC ${LIBMEXCLASS_CLIENT_MEX_GATEWAY_SOURCES}
                   OUTPUT_NAME "gateway"
                   NO_IMPLICIT_LINK_TO_MATLAB_LIBRARIES
                   LINK_TO mexclass
                           ${LIBMEXCLASS_CLIENT_MEX_GATEWAY_CLIENT_PROXY_LIBRARY_NAME}
                           ${Matlab_MX_LIBRARY}
                           ${Matlab_MEX_LIBRARY}
                           ${Matlab_DATAARRAY_LIBRARY})
    # Set compiler features to require C++17.
    target_compile_features(${LIBMEXCLASS_CLIENT_MEX_GATEWAY_NAME} PRIVATE cxx_std_17)
    # Include directories (i.e. header files).
    get_target_property(LIBMEXCLASS_INCLUDE_DIRS mexclass INCLUDE_DIRECTORIES)
    target_include_directories(${LIBMEXCLASS_CLIENT_MEX_GATEWAY_NAME} PRIVATE ${LIBMEXCLASS_INCLUDE_DIRS})
    # TODO: Decide whether to automatically add client library include directories.
    get_target_property(LIBMEXCLASS_CLIENT_PROXY_LIBRARY_INCLUDE_DIRS ${LIBMEXCLASS_CLIENT_MEX_GATEWAY_CLIENT_PROXY_LIBRARY_NAME} INCLUDE_DIRECTORIES)
    target_include_directories(${LIBMEXCLASS_CLIENT_MEX_GATEWAY_NAME} PRIVATE ${LIBMEXCLASS_CLIENT_PROXY_LIBRARY_INCLUDE_DIRS})

    target_set_rpath_relocatable(NAME ${LIBMEXCLASS_CLIENT_MEX_GATEWAY_NAME})
endmacro()

# ############
# Installation
# ############

macro(libmexclass_client_install)
    set(options)
    set(oneValueArgs NAME CLIENT_PROXY_LIBRARY_NAME CLIENT_MEX_GATEWAY_NAME DESTINATION)
    set(multiValueArgs SOURCES)
    cmake_parse_arguments(LIBMEXCLASS_CLIENT_INSTALL "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    set(LIBMEXCLASS_PROXY_PACKAGE_DIRECTORY "+libmexclass/+proxy")
    set(LIBMEXCLASS_CLIENT_INSTALL_PROXY_PACKAGE_DESTINATION ${LIBMEXCLASS_CLIENT_INSTALL_DESTINATION}/${LIBMEXCLASS_PROXY_PACKAGE_DIRECTORY})

    install(TARGETS mexclass
                    ${LIBMEXCLASS_CLIENT_INSTALL_CLIENT_PROXY_LIBRARY_NAME}
                    ${LIBMEXCLASS_CLIENT_INSTALL_CLIENT_MEX_GATEWAY_NAME}
            DESTINATION ${LIBMEXCLASS_CLIENT_INSTALL_PROXY_PACKAGE_DESTINATION})

    get_target_property(MATLAB_SOURCE_DIR mexclassmatlab MATLAB_SOURCES)
    install(DIRECTORY ${MATLAB_SOURCE_DIR} DESTINATION ${LIBMEXCLASS_CLIENT_INSTALL_DESTINATION})

    get_target_property(LINK_LIBRARIES ${LIBMEXCLASS_CLIENT_INSTALL_CLIENT_PROXY_LIBRARY_NAME} LIBMEXCLASS_CLIENT_PROXY_LIBRARY_LINK_LIBRARIES)
    if(LINK_LIBRARIES)
        foreach(LINK_LIBRARY ${LINK_LIBRARIES})
            get_target_property(LINK_LIBRARY_IS_IMPORTED ${LINK_LIBRARY} IMPORTED)
            if(${LINK_LIBRARY_IS_IMPORTED})
                install_imported_target(NAME ${LINK_LIBRARY} DESTINATION ${LIBMEXCLASS_CLIENT_INSTALL_PROXY_PACKAGE_DESTINATION})
            else()
                install(TARGETS ${LINK_LIBRARY} DESTINATION ${LIBMEXCLASS_CLIENT_INSTALL_PROXY_PACKAGE_DESTINATION})
            endif()
        endforeach()
    endif()
endmacro()
