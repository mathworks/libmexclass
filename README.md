# libmexclass

## DISCLAIMERS

1. **NOTE**: The [MATLAB&reg; Interface to C++](https://www.mathworks.com/help/matlab/build-matlab-interface-to-c-library.html) is the recommended way to interface with C++ classes in MATLAB.

2. **NOTE**: `libmexclass` is **UNDER ACTIVE DEVELOPMENT**. It is **NOT** recommended for production use.

## Overview

`libmexclass` is a MATLAB framework which enables users to implement the functionality of MATLAB classes in terms of equivalent C++ classes using [MEX](https://www.mathworks.com/help/matlab/call-mex-files-1.html).

For MATLAB&reg; projects that are already using [MEX](https://www.mathworks.com/help/matlab/call-mex-files-1.html), `libmexclass` aims to provide an alternative for interfacing with C++ classes.

It is recommended to use `libmexclass` with CMake.

## Usage

### Technical Background

`libmexclass` enables client code to:

1. Implement MATLAB class methods in terms of equivalent C++ class methods using a MEX based proxying mechanism
2. Bound the lifetime of C++ objects to equivalent MATLAB objects

`libmexclass` is heavily inspired by the [Proxy Design Pattern](https://en.wikipedia.org/wiki/Proxy_pattern). Using `libmexclass` involves connecting `mexclass.Proxy` subclasses in MATLAB with corresponding `mexclass::Proxy` subclasses in C++.

### Getting Started

To use `libmexclass` in a MATLAB project, several steps are required, which are enumerated below.

#### 1. Subclass `mexclass::ProxyFactory` in C++

Create a subclass of `mexclass::ProxyFactory` in C++ with the name `CustomProxyFactory`.

`mexclass::ProxyFactory` is a ["simple factory"](https://en.wikipedia.org/wiki/Factory_(object-oriented_programming)#Terminology). `CustomProxyFactory` is responsible for returning subclasses of `mexclass::Proxy` which wrap "raw" C++ objects and control access to their state.

##### Notes

1. Your subclass *MUST* be named `CustomProxyFactory`.
2. Your filenames *MUST* be named `CustomProxyFactory.hpp` and `CustomProxyFactory.cpp`.
2. `CustomProxyFactory.hpp` and `CustomProxyFactory.cpp` *MUST* be in the same directory.

##### Examples

1. `example/CustomProxyFactory.hpp` and `example/CustomProxyFactory.cpp` provide an example of how to implement `CustomProxyFactory`.

#### 2. Subclass `mexclass.Proxy` in MATLAB

Create a subclass of `mexclass.Proxy` in MATLAB whose class name is **identical** to the string used in the `switch` statement inside of your `CustomProxyFactory` implementation.

##### Notes

1. If the names of your corresponding MATLAB and C++ `Proxy` subclasses don't match exactly, then `libmexclass` won't be able to connect them.

##### Examples

1. If you created a custom `mexclass::Proxy` subclass in C++ named `CustomProxy` and used the string `CustomProxy` in the `switch` statement inside of your `CustomProxyFactory` implementation, then the name of your `mexclass.Proxy` subclass in MATLAB *MUST* also be `CustomProxy`.

#### 3. Build and Install using CMake

To use `libmexclass` in a MATLAB project, use the [`ExternalProject_Add()`](https://cmake.org/cmake/help/latest/module/ExternalProject.html) CMake function.

```cmake
ExternalProject_Add(libmexclass
                    GIT_REPOSITORY https://github.com/mathworks/libmexclass
                    CMAKE_ARGS -D CUSTOM_PROXY_FACTORY_DIR=<custom-proxy-factory-dir>)
```

In the CMake code snippet above, replace `<custom-proxy-factory-dir>` with the location of your implementation of `CustomProxyFactory` relative to the `CMakeLists.txt` file for your project.

## MATLAB Version Compatibility

`libmexclass` is compatible with [MATLAB R2022a](https://www.mathworks.com/products/new_products/latest_features.html) or newer.

## Contributing

We welcome external contributions! Feel free to open a pull request!

For more information, see [CONTRIBUTING.md](CONTRIBUTING.md).

Copyright &copy; 2022, The MathWorks, Inc.


