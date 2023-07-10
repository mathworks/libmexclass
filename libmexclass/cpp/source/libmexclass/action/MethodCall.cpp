#include "libmexclass/action/MethodCall.h"
#include "libmexclass/mex/State.h"
#include "libmexclass/proxy/Proxy.h"
#include "libmexclass/proxy/ID.h"
#include "libmexclass/proxy/ProxyManager.h"
#include "libmexclass/proxy/method/Method.h"

namespace libmexclass::action {

std::optional<libmexclass::error::Error> MethodCall::execute() {
    // TODO: Implement ID retrieval logic from MethodCall properties.
    // Retrieve the appropriate polymorphic proxy::Proxy instance from the
    // proxy::ProxyManager using the given proxy::ID.
    auto proxy = libmexclass::proxy::ProxyManager::getProxy(proxy_id);

    if (!proxy) {
        return libmexclass::error::Error{"libmexclass:proxy:UnknownProxyID", "Unknown proxy ID " + std::to_string(proxy_id)};
    }

    // Invoke the appropriate method on the proxy::Proxy instance.
    // Note: To assign/return outputs from a method call, proxy::Proxy
    // instances can assign to state.outputs ( which is a
    // std::vector<matlab::data::Array>).
    // TODO: Consider passing method_arguments to proxy instead.
    libmexclass::proxy::method::Method method{method_name, method_arguments,
                                              outputs, matlab};
    proxy->invoke(method);
    
    // return an error if one exists. Otherwise returns a nullopt.
    return method.context.error;
}

} // namespace libmexclass::action
