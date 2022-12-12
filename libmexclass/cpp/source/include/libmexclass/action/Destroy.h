#pragma once

#include "libmexclass/action/Action.h"
#include "libmexclass/mex/State.h"
#include "libmexclass/proxy/ID.h"

namespace libmexclass::action {

    class Destroy : public Action {
        public:
            Destroy(libmexclass::mex::State& state) : Action(state) {
                // TODO: Implement input validation.
                proxy_id = std::uint64_t(state.inputs[libmexclass::action::Destroy::PROXY_ID_INDEX][0]);
            }
            virtual ~Destroy() {}
            virtual void execute() override;
        private:
            libmexclass::proxy::ID proxy_id;

            static inline const std::uint64_t PROXY_ID_INDEX = 1;
    };
    
}
