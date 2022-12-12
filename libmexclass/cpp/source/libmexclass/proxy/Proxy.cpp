#include "libmexclass/proxy/Proxy.h"

namespace libmexclass::proxy {
	void Proxy::invoke(libmexclass::proxy::method::Method& method) {
        // TODO: Handle unregistered / non-existent method names.
        methods[method.name](method.context);
    }
}
