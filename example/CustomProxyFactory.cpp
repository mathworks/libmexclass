#include "CustomProxyFactory.h"

#include "proxy/Car.h"

std::shared_ptr<libmexclass::proxy::Proxy>
CustomProxyFactory::make_proxy(const libmexclass::proxy::ClassName& class_name,
                               const libmexclass::proxy::FunctionArguments& constructor_arguments) {

    registerProxy(example.proxy.Car, example::proxy::Car);
    return nullptr;
}
