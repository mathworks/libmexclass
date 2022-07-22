sourceFiles = ["testMex.cpp", ...
               "Error.cpp", ...
               "../log/Logger.cpp"];
compilerFlags = "CXXFLAGS=$CXXFLAGS -std=c++17";
includeDirectories = ["-I.."];
verboseFlag = "-v";

mex(sourceFiles{:}, includeDirectories{:}, compilerFlags);