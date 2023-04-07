# Example

# Notes

1. **NOTE**: Replace `<install-prefix>` with your custom installation prefix in the command below.
2. **NOTE**: Replace `<git-tag>` with a valid Git commit hash string or Git branch name. By default, the `main` branch of `mathworks/libmexclass` will be used.
3. **NOTE**: The installation directory must be added to the MATLAB path to run the MEX gateway function.

# Build

```shell
$ rm -Rf build
$ cmake -S . -B build -D CMAKE_INSTALL_PREFIX=<install-prefix> -D LIBMEXCLASS_FETCH_CONTENT_GIT_TAG=<git-tag>
$ cmake --build build --config Release --target install
```

# Setup MATLAB Path

```matlab
>> LIBMEXCLASS_INSTALL_PREFIX = fullfile("<install-prefix>");
>> addpath(LIBMEXCLASS_INSTALL_PREFIX);
>> LIBMEXCLASS_SOURCE_DIR = fullfile("<libmexclass-source-dir>");
>> addpath(fullfile(LIBMEXCLASS_SOURCE_DIR, "example", "matlab"));
```
