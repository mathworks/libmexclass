#pragma once

#include "libmexclass/mex/ArgumentsIterator.h"

#include "MatlabDataArray.hpp"

namespace libmexclass::mex {
    // Simple class that wraps the internal iterator used by matlab::mex::ArgumentList.
    class Arguments {
        public:
            Arguments(ArgumentsIterator iterator) : iterator{iterator} {}

            matlab::data::Array& operator[](std::size_t i) { return *(iterator + i); }
        private:
            ArgumentsIterator iterator;
    };
}
