#pragma once

#include "proxy/Proxy.h"

class CustomProxy : public proxy::Proxy {
    virtual void proxy(proxy::Context& context) override;
};