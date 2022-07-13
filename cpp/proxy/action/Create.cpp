#include "proxy/Proxy.h"
#include "proxy/ID.h"
#include "proxy/ProxyManager.h"

#include "Create.h"

#include "MatlabDataArray.hpp"

namespace proxy {
    namespace action {

        void Create::execute(Context& context) {
            // TODO: Remove debug output.
            std::cout << "Executing 'Create' Action..." << std::endl;

            // proxy::ProxyFactory will create an appropriate proxy::Proxy subclass based on the provided proxy::Context.
            // proxy::Context contains the name of the proxy::Proxy subclass to create and manage with the proxy::ProxyManager
            // in proxy::Context::parameters::create_parameters.
            std::shared_ptr<Proxy> proxy = proxy_factory->make_proxy(context);

            // Assign the proxy::ID returned by the ProxyManager to the outputs[] MDA.
            ID id = ProxyManager::getProxyManager()->manageProxy(proxy);

            matlab::data::ArrayFactory factory;
            auto id_array = factory.createScalar<ID>(id);
            context.outputs[0] = id_array;
        }
        
    } // namespace action
} // namespace proxy