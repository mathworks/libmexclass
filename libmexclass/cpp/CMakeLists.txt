cmake_minimum_required(VERSION 3.0.0)

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

# Create libmexclassclient shared library target.
set(CLIENT_LIBRARY_NAME mexclassclient)
add_library(${CLIENT_LIBRARY_NAME} SHARED ${CUSTOM_PROXY_FACTORY_SOURCES} ${CUSTOM_PROXY_SOURCES})

# Set compiler features to require C++17.
target_compile_features(${CLIENT_LIBRARY_NAME} PRIVATE cxx_std_17)

# Include directories (i.e. header files).
target_include_directories(${CLIENT_LIBRARY_NAME} PRIVATE ${Matlab_INCLUDE_DIRS})
target_include_directories(${CLIENT_LIBRARY_NAME} PRIVATE ${LIBMEXCLASS_INCLUDE_DIR})
target_include_directories(${CLIENT_LIBRARY_NAME} PRIVATE ${CUSTOM_PROXY_FACTORY_INCLUDE_DIR})
target_include_directories(${CLIENT_LIBRARY_NAME} PRIVATE ${CUSTOM_PROXY_INCLUDE_DIR})

# Link against libmexclass shared library.
target_link_libraries(${CLIENT_LIBRARY_NAME} PRIVATE mexclass)
# Link against MATLAB Data Array shared library.
target_link_libraries(${CLIENT_LIBRARY_NAME} PRIVATE ${Matlab_DATAARRAY_LIBRARY})
# Link against custom proxy link libraries.
target_link_libraries(${CLIENT_LIBRARY_NAME} PRIVATE ${CUSTOM_PROXY_LINK_LIBRARIES})

# ###########
# MEX gateway
# ###########

# Create MEX gateway function target.
set(MEX_GATEWAY_NAME gateway)
set(MEX_GATEWAY_SOURCES ${LIBMEXCLASS_SOURCE_DIR}/libmexclass/mex/mex_gateway_function.cpp)
matlab_add_mex(NAME ${MEX_GATEWAY_NAME}
               SRC ${MEX_GATEWAY_SOURCES}
               LINK_TO ${LIBMEXCLASS_LIBRARY_NAME}
                       ${CLIENT_LIBRARY_NAME})
# Set compiler features to require C++17.
target_compile_features(${MEX_GATEWAY_NAME} PRIVATE cxx_std_17)
# Include directories (i.e. header files).
target_include_directories(${MEX_GATEWAY_NAME}
                           PRIVATE ${LIBMEXCLASS_INCLUDE_DIR}
                                   ${CUSTOM_PROXY_FACTORY_INCLUDE_DIR})

# ######################
# Installation Variables
# ######################

message(STATUS "LIBMEXCLASS_LIBRARY_NAME: ${LIBMEXCLASS_LIBRARY_NAME}")
message(STATUS "CLIENT_LIBRARY_NAME: ${CLIENT_LIBRARY_NAME}")
message(STATUS "CUSTOM_PROXY_RUNTIME_LIBRARIES: ${CUSTOM_PROXY_RUNTIME_LIBRARIES}")

set(ACTUAL_LIBMEXCLASS_BINARIES_DIR ${CMAKE_CURRENT_BINARY_DIR})
# TODO: Get the binary names and extensions using Matlab_MEX_EXTENSION in CMake FindMatlab.
if(WIN32)
    # On Windows, the Visual Studio build adds an additional "Release" folder to place the output binaries.
    # TODO: Use cmake-generator-expressions to figure out the actual folder.
    set(ACTUAL_LIBMEXCLASS_BINARIES_DIR "${ACTUAL_LIBMEXCLASS_BINARIES_DIR}/Release/")
    list(APPEND INSTALL_BINARIES_LIST ${ACTUAL_LIBMEXCLASS_BINARIES_DIR}/gateway.mexw64
                                      ${ACTUAL_LIBMEXCLASS_BINARIES_DIR}/mexclass.dll
                                      ${ACTUAL_LIBMEXCLASS_BINARIES_DIR}/${CLIENT_LIBRARY_NAME}.dll)
elseif(APPLE)
    list(APPEND INSTALL_BINARIES_LIST ${ACTUAL_LIBMEXCLASS_BINARIES_DIR}/gateway.mexmaci64
                                      ${ACTUAL_LIBMEXCLASS_BINARIES_DIR}/libmexclass.dylib
                                      ${ACTUAL_LIBMEXCLASS_BINARIES_DIR}/lib${CLIENT_LIBRARY_NAME}.dylib)
elseif(UNIX AND NOT APPLE AND NOT CYGWIN)
    list(APPEND INSTALL_BINARIES_LIST ${ACTUAL_LIBMEXCLASS_BINARIES_DIR}/gateway.mexa64
                                      ${ACTUAL_LIBMEXCLASS_BINARIES_DIR}/libmexclass.so
                                      ${ACTUAL_LIBMEXCLASS_BINARIES_DIR}/lib${CLIENT_LIBRARY_NAME}.so)
endif()
message(STATUS "ACTUAL_LIBMEXCLASS_BINARIES_DIR: ${ACTUAL_LIBMEXCLASS_BINARIES_DIR}")

set(LIBMEXCLASS_MATLAB_SOURCES "${CMAKE_CURRENT_BINARY_DIR}/../libmexclass/libmexclass/matlab/+libmexclass/")
message(STATUS "LIBMEXCLASS_MATLAB_SOURCES: ${LIBMEXCLASS_MATLAB_SOURCES}")

set(CMAKE_PACKAGED_LIBMEXCLASS_INSTALL_ROOT_DIR "${CMAKE_CURRENT_BINARY_DIR}/+libmexclass")
set(CMAKE_PACKAGED_LIBMEXCLASS_INSTALL_DIR "${CMAKE_PACKAGED_LIBMEXCLASS_INSTALL_ROOT_DIR}/+proxy/")
message(STATUS "CMAKE_PACKAGED_LIBMEXCLASS_INSTALL_DIR: ${CMAKE_PACKAGED_LIBMEXCLASS_INSTALL_DIR}")

# ########################
# Installation
# ########################

# Copy ${LIBMEXCLASS_MATLAB_SOURCES} first so that ${CMAKE_CURRENT_BINARY_DIR}/+libmexclass/+proxy/ folder is there to copy binaries to.
install(CODE "MESSAGE(\"Copying LIBMEXCLASS_MATLAB_SOURCES to packaged folder CMAKE_PACKAGED_LIBMEXCLASS_INSTALL_DIR...\")")
install(DIRECTORY ${LIBMEXCLASS_MATLAB_SOURCES} DESTINATION ${CMAKE_PACKAGED_LIBMEXCLASS_INSTALL_ROOT_DIR})

# Copy the binaries to ${CMAKE_CURRENT_BINARY_DIR}/+libmexclass/+proxy/ packaged folder.
install(CODE "MESSAGE(\"Copying libmexclass binaries from ACTUAL_LIBMEXCLASS_BINARIES_DIR to packaged folder CMAKE_PACKAGED_LIBMEXCLASS_INSTALL_DIR...\")")
install(FILES ${INSTALL_BINARIES_LIST} DESTINATION ${CMAKE_PACKAGED_LIBMEXCLASS_INSTALL_DIR})

# Copy CUSTOM_PROXY_RUNTIME_LIBRARIES to ${CMAKE_CURRENT_BINARY_DIR}/+libmexclass/+proxy/ packaged folder.
if(DEFINED CUSTOM_PROXY_RUNTIME_LIBRARIES)
install(CODE "MESSAGE(\"Copying CUSTOM_PROXY_RUNTIME_LIBRARIES to packaged folder CMAKE_PACKAGED_LIBMEXCLASS_INSTALL_DIR...\")")
install(FILES ${CUSTOM_PROXY_RUNTIME_LIBRARIES} DESTINATION ${CMAKE_PACKAGED_LIBMEXCLASS_INSTALL_DIR})
endif()
