#pragma once

#include "libmexclass/proxy/Factory.h"

#include "CustomProxy.h"

class CustomProxyFactory : public libmexclass::proxy::Factory {
    public:
        CustomProxyFactory() {
                std::cout << "[LOG::INFO] Constructor = CustomProxyFactory::CustomProxyFactory()" << std::endl;
        }
        virtual std::shared_ptr<libmexclass::proxy::Proxy> make_proxy(const libmexclass::proxy::ClassName& class_name, const libmexclass::proxy::FunctionArguments& constructor_arguments);
};
