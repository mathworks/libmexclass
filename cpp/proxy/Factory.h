#pragma once

#include <memory>

#include "proxy/Context.h"
#include "proxy/Proxy.h"

namespace proxy {

    // Abstract interface defining a class that is able to make Proxy objects from a given proxy::Context.
    // This interface uses the "Factory" design pattern.
    class Factory {
        public:
            virtual std::shared_ptr<Proxy> make_proxy(Context& context) = 0;
    };

}