#include "CustomProxyFactory.h"

std::shared_ptr<libmexclass::proxy::Proxy> CustomProxyFactory::make_proxy(const libmexclass::proxy::ClassName& class_name, const libmexclass::proxy::FunctionArguments& constructor_arguments) {
    // Pass constructor arguments from the libmexclass::mex::State to the constructor of specific proxy::Proxy subclass constructors.
    // TODO: This is a stub. For now, we will just return a single class, regardless of input.
    //       However, in the future, this should be a switch-yard, where we delegate to specific Proxy subclasses.
    return std::make_shared<CustomProxy>();
}
