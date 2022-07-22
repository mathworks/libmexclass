sourceFiles = ["testMex.cpp", ...
               "Logger.cpp"];
compilerFlags = "CXXFLAGS=$CXXFLAGS -std=c++17";
includeDirectories = ["-I.."];
verboseFlag = "-v";

mex(sourceFiles{:}, includeDirectories{:}, compilerFlags);