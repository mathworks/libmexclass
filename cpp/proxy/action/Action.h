#pragma once

#include "proxy/Context.h"

namespace proxy {
    namespace action {

        // Interface for Proxy Actions.
        // Actions include CREATE, DESTROY, and METHODCALL
        // Subclasses implementing the proxy::action::Action
        // interface must provide a concrete implementation for
        // the execute() method.
        class Action {
            public:
            virtual ~Action() {}
            virtual void execute(Context& context) = 0;
        };
    } // namespace action
} // namespace proxy