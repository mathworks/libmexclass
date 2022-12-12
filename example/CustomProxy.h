#pragma once

#include "libmexclass/proxy/Proxy.h"
#include "libmexclass/proxy/method/Context.h"

#include "Custom.h"

class CustomProxy : public libmexclass::proxy::Proxy {
    public:
        CustomProxy() : custom{} {
            registerMethod(CustomProxy, Print);
            registerMethod(CustomProxy, Foo);
        }
    private:
        // Note: This is a wrapper for the equivalent raw C++ method call.
        void Print(libmexclass::proxy::method::Context& context);
        void Foo(libmexclass::proxy::method::Context& context);

        // Note: Clients can replace this with whatever "raw" C++ Class they want
        // to proxy method calls to.
        Custom custom;
};
