#pragma once

#include "libmexclass/action/Action.h"

namespace libmexclass::action {

    class Unsupported : public Action {
        public:
            Unsupported(libmexclass::mex::State& state) : Action{state} {
            }
            virtual ~Unsupported() {}
            virtual void execute() override;
    };
    
}
