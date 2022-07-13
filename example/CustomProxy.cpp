#include "CustomProxy.h"

// TODO: Remove this. For debugging purposes.
#include <iostream>

void CustomProxy::proxy(proxy::Context& context) {
    // TODO: This is a stub.
    // In the future, this should be a switch-yard that delegates
    // to the appropriate raw object method call either via a helper function
    // or directly.
    std::cout << "Hello, world!" << std::endl;
}