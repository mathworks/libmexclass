#pragma once

#include "libmexclass/proxy/Factory.h"

class CarProxyFactory : public libmexclass::proxy::Factory {
  public:
    CarProxyFactory() {}
    virtual libmexclass::error::Result<std::shared_ptr<libmexclass::proxy::Proxy>>
    make_proxy(const libmexclass::proxy::ClassName& class_name,
               const libmexclass::proxy::FunctionArguments& constructor_arguments);
};
