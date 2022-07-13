#include "proxy/ProxyManager.h"
#include "proxy/ID.h"
#include "proxy/Proxy.h"

#include "MethodCall.h"

namespace proxy {
    namespace action {

        void MethodCall::execute(Context& context) {
            ID id = context.action_parameters.method_call_parameters.id;
            // Retrieve the appropriate polymorphic proxy::Proxy instance from the proxy::ProxyManager using the given proxy::ID.
            std::shared_ptr<Proxy> proxy = ProxyManager::getProxyManager()->getProxy(id);
            
            // Invoke the appropriate method on the proxy::Proxy instance.
            // Note: To assign/return outputs from a method call, proxy::Proxy instances can assign to context.outputs (which is a std::vector<matlab::data::Array>).
            proxy->proxy(context);
        }

    } // namespace action
} // namespace proxy