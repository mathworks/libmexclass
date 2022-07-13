#pragma once

#include "proxy/action/Action.h"
#include "proxy/ID.h"
#include "proxy/Proxy.h"
#include "proxy/ProxyManager.h"

namespace proxy {
    namespace action {

        class MethodCall : public Action {
            public:
            virtual ~MethodCall() {}
            virtual void execute(Context& context) override;
        };

    } // namespace action
} // namespace proxy