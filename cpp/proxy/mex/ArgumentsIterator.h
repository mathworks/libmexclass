#pragma once

#include "MatlabDataArray.hpp"

namespace libmexclass::mex {
    // Iterator type used by matlab::mex::ArgumentList.
    using ArgumentsIterator = typename std::vector<matlab::data::Array>::iterator;
}