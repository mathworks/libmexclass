#include "CarProxyFactory.h"

#include "proxy/Car.h"

libmexclass::proxy::MakeProxyResult CarProxyFactory::make_proxy(const libmexclass::proxy::ClassName& class_name,
                            const libmexclass::proxy::FunctionArguments& constructor_arguments) {

    REGISTER_PROXY(example.proxy.Car, example::proxy::Car);

    return libmexclass::error::Error{"libmexclass:proxy:factory:failed", "Failed to make proxy"};
}
