#pragma once

#include "libmexclass/proxy/method/Inputs.h"
#include "libmexclass/proxy/method/Outputs.h"
#include "libmexclass/proxy/method/Matlab.h"

namespace libmexclass::proxy::method {

    struct Context {
        const libmexclass::proxy::method::Inputs inputs;
        libmexclass::proxy::method::Outputs outputs;
        const libmexclass::proxy::method::Matlab matlab;
    };

}
