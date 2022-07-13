#include "Destroy.h"

#include "proxy/ProxyManager.h"
#include "proxy/ID.h"

namespace proxy {
    namespace action {

        void Destroy::execute(Context& context) {
            // Remove the proxy::Proxy instance specified by the given proxy::ID from the proxy::ProxyManager.
            // This should also deallocate any associated memory (unless there is a shared_ptr to the proxy
            // being held somewhere else).
            ID id = context.action_parameters.destroy_parameters.id;
            ProxyManager::getProxyManager()->unmanageProxy(id);
        }

    } // namespace action
} // namespace proxy