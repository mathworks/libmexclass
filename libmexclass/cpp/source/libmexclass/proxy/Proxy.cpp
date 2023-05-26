#include "libmexclass/proxy/Proxy.h"

namespace libmexclass::proxy {
	std::optional<libmexclass::error::Error> Proxy::invoke(libmexclass::proxy::method::Method& method) {
        // TODO: Handle unregistered / non-existent method names.
        methods[method.name](method.context);
        return method.context.error;
    }
}
