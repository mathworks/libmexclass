cmake_minimum_required(VERSION 3.0.0)

set(PROJECT_NAME libmexclass)
set(LIBRARY_NAME libmexclass)
set(CMAKE_SHARED_LIBRARY_PREFIX "lib_")
set(libmexclass_sources
    cpp/proxy/mex/mex_gateway_function.cpp
    cpp/proxy/action/TypeFactory.cpp
    cpp/proxy/action/Unsupported.cpp
    cpp/proxy/action/Create.cpp
    cpp/proxy/action/Destroy.cpp
    cpp/proxy/action/MethodCall.cpp
    cpp/proxy/ProxyManager.cpp
    example/CustomProxy.cpp
    example/CustomProxyFactory.cpp 
)
set(MY_DEBUG_OPTIONS -std=c++17 -I cpp/)
set(MY_RELEASE_OPTIONS -std=c++17)

project(${PROJECT_NAME} VERSION 0.1.0)
add_library(${LIBRARY_NAME} SHARED ${libmexclass_sources})

find_package(Matlab REQUIRED COMPONENTS MEX_COMPILER)
message(STATUS "Mex Library: ${Matlab_MEX_LIBRARY}")
message(STATUS "Mex Include Folder: ${Matlab_INCLUDE_DIRS}")

target_include_directories(${LIBRARY_NAME} PRIVATE ${Matlab_INCLUDE_DIRS})
target_include_directories(${LIBRARY_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/)
target_include_directories(${LIBRARY_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/cpp/)

target_compile_options(${LIBRARY_NAME} PUBLIC "$<$<CONFIG:DEBUG>:${MY_DEBUG_OPTIONS}>")
target_compile_options(${LIBRARY_NAME} PUBLIC "$<$<CONFIG:RELEASE>:${MY_RELEASE_OPTIONS}>")
