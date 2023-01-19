#include "CustomProxyFactory.h"

#include "Car.h"
#include "CarProxy.h"

std::shared_ptr<libmexclass::proxy::Proxy>
CustomProxyFactory::make_proxy(const libmexclass::proxy::ClassName& class_name,
                               const libmexclass::proxy::FunctionArguments& constructor_arguments) {

    REGISTER_PROXY(example.detail.CarProxy, libmexclass::example::CarProxy);
    return nullptr;
}
