# Example libmexclass client

1. **NOTE**: Replace `<install-prefix>` with your custom installation prefix in the command below.
2. **NOTE**: The installation directory must be added to the MATLAB path to run the MEX gateway function.

```shell
$ rm -Rf build; cmake -S . -B build -D CMAKE_CXX_COMPILER_LAUNCHER=ccache -D CMAKE_INSTALL_PREFIX=<install-prefix>; cmake --build build --config Release --target install
```
