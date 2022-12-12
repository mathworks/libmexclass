#pragma once

namespace libmexclass::proxy::method {
    template<typename ProxyClass>
    using Pointer = void (ProxyClass::*)(const libmexclass::proxy::method::Context&);
}
