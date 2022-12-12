#pragma once

#include "libmexclass/proxy/ClassName.h"
#include "libmexclass/proxy/FunctionArguments.h"
#include "libmexclass/mex/State.h"
#include "libmexclass/proxy/Proxy.h"

#include <memory>

namespace libmexclass::proxy {

    // Abstract interface defining a class that is able to make Proxy objects with a particular ClassName and ConstructorArguments.
    // This interface uses the "Factory" design pattern.
    class Factory {
        public:
            virtual std::shared_ptr<Proxy> make_proxy(const libmexclass::proxy::ClassName& class_name, const libmexclass::proxy::FunctionArguments& constructor_arguments) = 0;
    };

}
