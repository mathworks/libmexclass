#pragma once

#include "libmexclass/action/Action.h"
#include "libmexclass/proxy/FunctionArguments.h"
#include "libmexclass/proxy/ID.h"
#include "libmexclass/proxy/method/Name.h"
#include "libmexclass/proxy/Proxy.h"

namespace libmexclass::action {

    class MethodCall : public Action {
        public:
            MethodCall(libmexclass::mex::State& state) : Action{state} {
                proxy_id = std::uint64_t(state.inputs[libmexclass::action::MethodCall::PROXY_ID_INDEX][0]);
                method_name = std::string(state.inputs[libmexclass::action::MethodCall::METHOD_NAME_INDEX][0]);
                method_arguments = state.inputs[libmexclass::action::MethodCall::METHOD_ARGUMENTS_INDEX];
            }
            virtual ~MethodCall() {}
            virtual void execute() override;
        private:
            libmexclass::proxy::ID proxy_id;
            libmexclass::proxy::method::Name method_name;
            libmexclass::proxy::FunctionArguments method_arguments;

            static inline const std::uint64_t PROXY_ID_INDEX = 1;
            static inline const std::uint64_t METHOD_NAME_INDEX = 2;
            static inline const std::uint64_t METHOD_ARGUMENTS_INDEX = 3; 
    };
    
}
