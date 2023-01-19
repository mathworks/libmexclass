#pragma once

#include "libmexclass/proxy/ClassName.h"
#include "libmexclass/proxy/FunctionArguments.h"
#include "libmexclass/mex/State.h"
#include "libmexclass/proxy/Proxy.h"

#include <memory>

/*
* \brief register a fully specified MATLAB Class with it's associated C++ class.
* \param matlabClassName the name of the MATLAB class, e.g. myclass.MyClassProxy
* \param cxxClassName the name of the associated C++ class, e.g. myclass::MyClassProxy
*/
#define REGISTER_PROXY(matlabClassName, cxxClassName) if (class_name.compare(#matlabClassName) == 0) return std::make_shared<cxxClassName>(constructor_arguments)
/*
* \brief Convenience for registering a MATLAB class with the same name as its associated C++ class
* \param className e.g. MyClassProxy
*/
#define REGISTER_PROXY_SAME_NAME(className) REGISTER_PROXY(className, className)


namespace libmexclass::proxy {

    // Abstract interface defining a class that is able to make Proxy objects with a particular ClassName and ConstructorArguments.
    // This interface uses the "Factory" design pattern.
    class Factory {
        public:
            virtual std::shared_ptr<Proxy> make_proxy(const libmexclass::proxy::ClassName& class_name, const libmexclass::proxy::FunctionArguments& constructor_arguments) = 0;
    };

}
