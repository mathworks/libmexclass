# Example

1. **NOTE**: Replace `<install-prefix>` with your custom installation prefix in the command below.
2. **NOTE**: The installation directory must be added to the MATLAB path to run the MEX gateway function.

```shell
$ rm -Rf build
$ cmake -S . -B build -D CMAKE_INSTALL_PREFIX=<install-prefix>
$ cmake --build build --config Release --target install
```

# Setup MATLAB Path

```matlab
CMAKE_INSTALL_PREFIX = fullfile("<cmake-install-prefix>");
addpath(fullfile(CMAKE_INSTALL_PREFIX, "libmexclassInstall"));

LIBMEXCLASS_SOURCE_DIR = fullfile("<libmexclass-source-dir>");
addpath(fullfile(LIBMEXCLASS_SOURCE_DIR, "example", "matlab"));
```
