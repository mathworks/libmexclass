#include "libmexclass/action/Destroy.h"
#include "libmexclass/mex/State.h"
#include "libmexclass/proxy/ID.h"
#include "libmexclass/proxy/ProxyManager.h"

namespace libmexclass::action {

        void Destroy::execute() {
            // Remove the proxy::Proxy instance specified by the given proxy::ID from the proxy::ProxyManager.
            // This should also deallocate any associated memory (unless there is a shared_ptr to the proxy
            // being held somewhere else).
            libmexclass::proxy::ProxyManager::getProxyManager()->unmanageProxy(proxy_id);
        }

}
