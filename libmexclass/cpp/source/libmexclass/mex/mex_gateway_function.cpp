#include "libmexclass/action/Action.h"
#include "libmexclass/action/Factory.h"
#include "libmexclass/mex/Arguments.h"
#include "libmexclass/mex/State.h"
#include "libmexclass/proxy/Factory.h"

// TODO: Consider making the directory a preprocessor definition based on the client's CMakeLists.txt
// #include "CUSTOM_PROXY_FACTORY_DIR/CustomProxyFactory.h"
#include "CustomProxyFactory.h"

#include "mex.hpp"
#include "mexAdapter.hpp"

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
class MexFunction : public matlab::mex::Function {
    public:
    void operator()(matlab::mex::ArgumentList outputs, matlab::mex::ArgumentList inputs) {
        using namespace libmexclass;

        // Wrap the inputs and outputs.
        mex::Arguments output_arguments{outputs.begin()};
        mex::Arguments input_arguments{inputs.begin()};

        // Store the inputs, outputs, and MATLAB Engine pointer in a libmexclass::mex::State instance.
        mex::State state{input_arguments, output_arguments, getEngine()};

        // Create a polymorphic proxy::Factory instance.
        // NOTE: Clients provide the implementation for CustomProxyFactory.
        std::shared_ptr<proxy::Factory> proxy_factory = std::make_shared<CustomProxyFactory>();

        // Create an action::Factory.
        action::Factory action_factory{proxy_factory};

        // Create an Action.
        std::unique_ptr<action::Action> action = action_factory.makeAction(state);
        
        // Execute the Action.
        action->execute();
    }
};
