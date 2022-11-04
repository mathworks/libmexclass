# avoid hardcoding env specific vars
# line 4,9
# line9: use find_package()
cmake_minimum_required(VERSION 3.0.0)
set(PROJECT_NAME libmexclass)
set(LIBRARY_NAME libmexclass)
# set(CURRENT_DIR ${CMAKESRC DIR})
project(${PROJECT_NAME} VERSION 0.1.0)

# target_include_directories or include_directoris(global modifications)?
# scope configs
include_directories(/mnt/c/Program\ Files/MATLAB/R2022b/extern/include/)
# include_directories(${CURRENT_DIR}/)
# include_directories(${CURRENT_DIR}/cpp/)

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

add_library(${LIBRARY_NAME} SHARED ${libmexclass_sources})

# set(MY_DEBUG_OPTIONS -std=c++17 -I cpp/)
# set(MY_RELEASE_OPTIONS -std=c++17)

# target_compile_options(${LIBRARY_NAME} PUBLIC "$<$<CONFIG:DEBUG>:${MY_DEBUG_OPTIONS}>")
# target_compile_options(${LIBRARY_NAME} PUBLIC "$<$<CONFIG:RELEASE>:${MY_RELEASE_OPTIONS}>")

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)
