#include "libmexclass/action/Create.h"
#include "libmexclass/mex/State.h"
#include "libmexclass/proxy/Proxy.h"
#include "libmexclass/proxy/ID.h"
#include "libmexclass/proxy/ProxyManager.h"

#include "MatlabDataArray.hpp"

namespace libmexclass::action {

        void Create::execute() {
            // proxy::ProxyFactory will create an appropriate proxy::Proxy subclass based on the provided libmexclass::mex::State.
            std::shared_ptr<libmexclass::proxy::Proxy> proxy = proxy_factory->make_proxy(class_name, constructor_arguments);

            // Assign the proxy::ID returned by the ProxyManager to the outputs[] MDA.
            libmexclass::proxy::ID id = libmexclass::proxy::ProxyManager::getProxyManager()->manageProxy(proxy);

            matlab::data::ArrayFactory factory;
            auto id_array = factory.createScalar<libmexclass::proxy::ID>(id);
            outputs[0] = id_array;
        }
        
}
