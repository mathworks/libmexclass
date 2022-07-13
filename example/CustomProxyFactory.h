#pragma once

#include "proxy/Factory.h"

#include "CustomProxy.h"

class CustomProxyFactory : public proxy::Factory {
    public:
        CustomProxyFactory() {
                std::cout << "Constructing CustomProxyFactory..." << std::endl;
        }
        virtual std::shared_ptr<proxy::Proxy> make_proxy(proxy::Context& context);
};