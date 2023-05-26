#pragma once

#include "libmexclass/error/Error.h"

#include <variant>

namespace libmexclass::error {

template<typename T>
using Result = std::variant<T, Error>;
}

