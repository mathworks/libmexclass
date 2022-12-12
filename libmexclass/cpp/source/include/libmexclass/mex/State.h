#pragma once

#include "libmexclass/mex/Arguments.h"
#include "libmexclass/mex/Matlab.h"

#include "MatlabDataArray.hpp"

namespace libmexclass::mex {
    struct State {
            libmexclass::mex::Arguments& inputs;
            libmexclass::mex::Arguments& outputs;
            libmexclass::mex::Matlab matlab;
    };
}
