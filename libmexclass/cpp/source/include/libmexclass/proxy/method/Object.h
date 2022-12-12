#pragma once

#include <functional>

namespace libmexclass::proxy::method {
    using Object = std::function<void(libmexclass::proxy::method::Context&)>;
}
