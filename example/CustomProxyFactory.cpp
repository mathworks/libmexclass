#include "CustomProxyFactory.h"

#include "CarProxy.h"

std::shared_ptr<libmexclass::proxy::Proxy> CustomProxyFactory::make_proxy(const libmexclass::proxy::ClassName& class_name, const libmexclass::proxy::FunctionArguments& constructor_arguments) {
    registerProxy(CarProxy);
    // TODO: Handle case where input class name does not match any of the registered proxy classes.
    return nullptr;
}
