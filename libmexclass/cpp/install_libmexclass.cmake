message(STATUS "Executing LIBMEXCLASS_INSTALL_STEPS_FILE: ${CMAKE_CURRENT_LIST_FILE} using INSTALL_COMMAND...")

set(LIBMEXCLASS_MATLAB_SOURCES "${CMAKE_CURRENT_BINARY_DIR}/../libmexclass/libmexclass/matlab/+libmexclass/")
message(STATUS "LIBMEXCLASS_MATLAB_SOURCES: ${LIBMEXCLASS_MATLAB_SOURCES}")

# Copy ${LIBMEXCLASS_MATLAB_SOURCES} first so that ${CMAKE_CURRENT_BINARY_DIR}/+libmexclass/+proxy/ folder is there to which we copy necessary binaries.
set(CMAKE_PACKAGED_LIBMEXCLASS_INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}/+libmexclass")
message(STATUS "CMAKE_PACKAGED_LIBMEXCLASS_INSTALL_DIR: ${CMAKE_PACKAGED_LIBMEXCLASS_INSTALL_DIR}")
message(STATUS "Copying LIBMEXCLASS_MATLAB_SOURCES to packaged folder CMAKE_PACKAGED_LIBMEXCLASS_INSTALL_DIR...")
file(COPY ${LIBMEXCLASS_MATLAB_SOURCES} DESTINATION ${CMAKE_PACKAGED_LIBMEXCLASS_INSTALL_DIR})

set(ACTUAL_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})
# TODO: Get the binary names and extensions using Matlab_MEX_EXTENSION in CMake FindMatlab.
if(WIN32)
	# On Windows, the Visual Studio build adds an additional "Release" folder to place the output binaries.
	set(ACTUAL_BINARY_DIR "${ACTUAL_BINARY_DIR}/Release/")
	list(APPEND INSTALL_BINARIES_LIST ${ACTUAL_BINARY_DIR}/gateway.mexw64 ${ACTUAL_BINARY_DIR}/mexclass.dll)	
elseif(APPLE)	
	list(APPEND INSTALL_BINARIES_LIST ${ACTUAL_BINARY_DIR}/gateway.mexmaci64 ${ACTUAL_BINARY_DIR}/libmexclass.dylib)
elseif(UNIX AND NOT APPLE AND NOT CYGWIN)
	list(APPEND INSTALL_BINARIES_LIST ${ACTUAL_BINARY_DIR}/gateway.mexa64 ${ACTUAL_BINARY_DIR}/libmexclass.so)
endif()
message(STATUS "ACTUAL_BINARY_DIR: ${ACTUAL_BINARY_DIR}")

# Copy the binaries to ${CMAKE_CURRENT_BINARY_DIR}/+libmexclass/+proxy/ packaged folder.
message(STATUS "Copying libmexclass binaries from ACTUAL_BINARY_DIR to packaged folder CMAKE_PACKAGED_LIBMEXCLASS_INSTALL_DIR...")
file(COPY ${INSTALL_BINARIES_LIST} DESTINATION ${CMAKE_PACKAGED_LIBMEXCLASS_INSTALL_DIR}/+proxy/)