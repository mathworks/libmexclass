cmake_minimum_required(VERSION 3.0.0)

# Project metadata.
set(LIBMEXCLASS_PROJECT_NAME libmexclass)
project(${LIBMEXCLASS_PROJECT_NAME} VERSION 0.1.0)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# Find MATLAB.
find_package(Matlab REQUIRED)

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

# Create MEX gateway function target.
set(MEX_GATEWAY_NAME gateway)
set(MEX_GATEWAY_SOURCES ${LIBMEXCLASS_SOURCE_DIR}/libmexclass/mex/mex_gateway_function.cpp)
matlab_add_mex(NAME ${MEX_GATEWAY_NAME}
               SRC ${MEX_GATEWAY_SOURCES}
                   ${CUSTOM_PROXY_FACTORY_SOURCES}
                   ${CUSTOM_PROXY_SOURCES}
               LINK_TO ${LIBMEXCLASS_LIBRARY_NAME}
                       ${CUSTOM_PROXY_LINK_LIBRARIES})
# Set compiler features to require C++17.
target_compile_features(${MEX_GATEWAY_NAME} PRIVATE cxx_std_17)
# Include directories (i.e. header files).
target_include_directories(${MEX_GATEWAY_NAME}
    PRIVATE ${LIBMEXCLASS_INCLUDE_DIR}
            ${CUSTOM_PROXY_FACTORY_INCLUDE_DIR}
            ${CUSTOM_PROXY_INCLUDE_DIR})

get_target_property(MEX_INCLUDE_DIRS ${MEX_GATEWAY_NAME} INCLUDE_DIRECTORIES)

message(status "****************** MEX_INCLUDE_DIRS: ${MEX_INCLUDE_DIRS}")
