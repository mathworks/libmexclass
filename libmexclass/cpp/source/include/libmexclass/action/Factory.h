#pragma once

#include "libmexclass/action/Action.h"
#include "libmexclass/action/Create.h"
#include "libmexclass/action/Destroy.h"
#include "libmexclass/action/MethodCall.h"
#include "libmexclass/action/Type.h"
#include "libmexclass/action/TypeFactory.h"
#include "libmexclass/action/Unsupported.h"
#include "libmexclass/mex/State.h"

#include "MatlabDataArray.hpp"

#include <memory>

namespace libmexclass::action {

    class Factory {
        public:
        Factory(std::shared_ptr<proxy::Factory> proxy_factory) : proxy_factory{proxy_factory} {

        }
        std::unique_ptr<Action> makeAction(libmexclass::mex::State& state) {
            // TODO: Implement input validation and parsing logic.
            // TODO: Check on string encoding.
            const auto action_type_string = std::string(state.inputs[0][0]);
            const libmexclass::action::TypeFactory type_factory;
            const auto action_type = type_factory.make_type(action_type_string);
            switch (action_type) {
                case libmexclass::action::Type::Create:
                    return std::make_unique<libmexclass::action::Create>(state, proxy_factory);
                    break;
                case libmexclass::action::Type::Destroy:
                    return std::make_unique<libmexclass::action::Destroy>(state);
                    break;
                case libmexclass::action::Type::MethodCall:
                    return std::make_unique<libmexclass::action::MethodCall>(state);
                    break;
                default: // Type::Unsupported
                    return std::make_unique<libmexclass::action::Unsupported>(state);
            }
        }

        private:
        std::shared_ptr<proxy::Factory> proxy_factory;

    };

}
