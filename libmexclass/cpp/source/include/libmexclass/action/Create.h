#pragma once

#include "libmexclass/proxy/Factory.h"
#include "libmexclass/proxy/FunctionArguments.h"
#include "libmexclass/action/Action.h"

#include <memory>

namespace libmexclass::action {

    class Create : public Action {
        public:
            Create(libmexclass::mex::State& state, std::shared_ptr<proxy::Factory> proxy_factory) : Action{state}, proxy_factory{proxy_factory} {
                // TODO: Remove debug output.
                std::cout << "[LOG::INFO] Constructor = action::Create ..." << std::endl;

                // TODO: Implement input validation.
                class_name = std::string(state.inputs[libmexclass::action::Create::CLASS_NAME_INDEX][0]);
                // TODO: This should be a cell array, correct?
                constructor_arguments = state.inputs[libmexclass::action::Create::CONSTRUCTOR_ARGUMENTS_INDEX];

                // TODO: Remove debug output.
                std::cout << "[LOG::INFO] action::Create | ClassName = " << this->class_name << std::endl;
            }
            virtual ~Create() {}
            virtual void execute() override;

        private:
            std::shared_ptr<proxy::Factory> proxy_factory;
            libmexclass::proxy::ClassName class_name;
            libmexclass::proxy::FunctionArguments constructor_arguments;

            static inline const std::uint64_t CLASS_NAME_INDEX = 1;
            static inline const std::uint64_t CONSTRUCTOR_ARGUMENTS_INDEX = 2;
    };
    
}
