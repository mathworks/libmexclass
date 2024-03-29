#pragma once

#include "libmexclass/proxy/ClassName.h"
#include "libmexclass/proxy/FunctionArguments.h"
#include "libmexclass/mex/State.h"
#include "libmexclass/proxy/Proxy.h"

#include <memory>

/*
* \brief register a C++ Proxy subclass so that a MATLAB Proxy instance can connect with it
* \param name the name that a MATLAB Proxy instance will use to connect with the registered C++ Proxy subclass
* \param cppClass the name of the C++ Proxy subclass to register
* \note The C++ Proxy class must define a static make function with the following signature:
*       libmexclass::error::Result<std::shared_ptr<cppClass>> make(libmexclass::proxy::FunctionArguments&).
*/

#define REGISTER_PROXY(name, cppClass) if (class_name.compare(#name) == 0) return cppClass::make(constructor_arguments)

namespace libmexclass::proxy {


    // Abstract interface defining a class that is able to make Proxy objects with a particular ClassName and ConstructorArguments.
    // This interface uses the "Factory" design pattern.
    class Factory {
        public:
        virtual libmexclass::proxy::MakeResult make_proxy(const libmexclass::proxy::ClassName& class_name, const libmexclass::proxy::FunctionArguments& constructor_arguments) = 0;
    };

}
