#pragma once

#include "libmexclass/mex/State.h"

namespace libmexclass::action {

        // Interface for Proxy Actions.
        // Actions include Create, Destroy, and MethodCall.
        // Subclasses implementing the proxy::action::Action
        // interface must provide a concrete implementation for
        // the execute() method.
        class Action {
            public:
                Action(libmexclass::mex::State& state) : outputs{state.outputs}, matlab{state.matlab} { }
                virtual ~Action() {}
                virtual void execute() = 0;
            protected:
                libmexclass::mex::Arguments& outputs;
                libmexclass::mex::Matlab matlab;
        };
        
}
