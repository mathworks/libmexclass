#pragma once

#include "MatlabDataArray.hpp"

#include "ArgumentsIterator.h"

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