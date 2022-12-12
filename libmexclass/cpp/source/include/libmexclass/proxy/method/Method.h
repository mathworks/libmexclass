#pragma once

#include "libmexclass/proxy/method/Context.h"
#include "libmexclass/proxy/method/Name.h"

namespace libmexclass::proxy::method {
    struct Method {
        const libmexclass::proxy::method::Name name;
        libmexclass::proxy::method::Context context;
    };
}
