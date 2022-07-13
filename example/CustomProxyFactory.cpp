#include "CustomProxyFactory.h"

std::shared_ptr<proxy::Proxy> CustomProxyFactory::make_proxy(proxy::Context& context) {
    // Pass constructor arguments from context to the constructor of specific proxy::Proxy subclass constructors.
    // TODO: This is a stub. For now, we will just return a single class, regardless of input.
    //       However, in the future, this should be a switch-yard, where we delegate to specific Proxy subclasses.
    return std::make_shared<CustomProxy>();
}