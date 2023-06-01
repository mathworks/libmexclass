#pragma once

#include "libmexclass/action/Action.h"
#include "libmexclass/action/Factory.h"
#include "libmexclass/mex/Arguments.h"
#include "libmexclass/mex/Matlab.h"
#include "libmexclass/mex/State.h"
#include "libmexclass/proxy/Factory.h"
#include "libmexclass/error/Error.h"

#include "mex.hpp"
#include "mexAdapter.hpp"

namespace libmexclass::mex {
// =======================================
// MEX Gateway Function Supported Syntaxes
// =======================================
//
// --------------------------------------------------------------------
//
// ====================
// action::Create
// ====================
//
// **NOTE** <proxy-constructor-args should be a cell array.
//
// >> <proxy-id> = libmexclass.proxy.gateway("Create", <proxy-name>, <proxy-constructor-args>)
//
// --------------------------------------------------------------------
//
// ====================
// action::MethodCall
// ====================
//
// **NOTE** <method-args> should be a cell array.
//
// >> <proxy-method-outputs> = libmexclass.proxy.gateway("MethodCall", <proxy-id>, <proxy-method-name>, <proxy-method-args>)
//
// --------------------------------------------------------------------
// 
// ====================
// action::Destroy 
// ====================
//
// >> <proxy-destroy-status> = libmexclass.proxy.gateway("Destroy", "<proxy-id>")
//
// ==================

// This is the main MEX function gateway.
// This uses a rough approximation of the "Proxy" Design Pattern to handle dispatching to appropriate object method calls.
    template<typename ProxyFactory>
    inline void gateway(matlab::mex::ArgumentList inputs, matlab::mex::ArgumentList outputs, Matlab matlab) {
        // Wrap the inputs and outputs.
        mex::Arguments output_arguments{outputs.begin()};
        mex::Arguments input_arguments{inputs.begin()};

        // Store the inputs, outputs, and MATLAB Engine pointer in a libmexclass::mex::State instance.
        mex::State state{input_arguments, output_arguments, matlab};

        // Create a polymorphic proxy::Factory instance.
        // NOTE: Clients provide the implementation for CustomProxyFactory.
        std::shared_ptr<proxy::Factory> proxy_factory = std::make_shared<ProxyFactory>();

        // Create an action::Factory.
        action::Factory action_factory{proxy_factory};

        // Create an Action.
        std::unique_ptr<action::Action> action = action_factory.makeAction(state);
        
        // Execute the Action.
        std::optional<error::Error> maybe_error = action->execute();
        if (maybe_error) {
            matlab::data::ArrayFactory factory;

            auto error = maybe_error.value();
            matlab::data::StructArray errorStruct = factory.createStructArray({1, 1}, {"identifier", "message"});
            errorStruct[0]["identifier"] = factory.createScalar(matlab::engine::convertUTF16StringToUTF8String(error.id));
            errorStruct[0]["message"] = factory.createScalar(matlab::engine::convertUTF16StringToUTF8String(error.message));
            matlab->feval(u"error", 0, std::vector<matlab::data::Array>({errorStruct}));
        }
    }
}
