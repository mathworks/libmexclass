#include "mex.hpp"
#include "mexAdapter.hpp"

#include "proxy/Context.h"
#include "proxy/Factory.h"
#include "proxy/action/Factory.h"
#include "proxy/action/Action.h"
#include "proxy/mex/Arguments.h"

// TODO: Consider making the directory a preprocessor definition based on the client's CMakeLists.txt
// #include "CUSTOM_PROXY_FACTORY_DIR/CustomProxyFactory.h"
#include "example/CustomProxyFactory.h"

// This is the main MEX function gateway.
// This uses a rough approximation of the "Proxy" Design Pattern to handle dispatching to appropriate object calls.
// Sample function calls: 
//      - proxy_ID = mex_gateway_function("CREATE", "CustomClass", "input1", "input2")
//      - output = mex_gateway_function("METHOD_CALL", proxy_ID, "input1", "input2")
//      - mex_gateway_function("DESTROY", proxy_ID)
class MexFunction : public matlab::mex::Function {
    public:
    void operator()(matlab::mex::ArgumentList outputs, matlab::mex::ArgumentList inputs) {
        using namespace libmexclass;

        // Wrap the inputs and outputs.
        mex::Arguments output_arguments{outputs.begin()};
        mex::Arguments input_arguments{inputs.begin()};

        // Store the inputs, outputs, and MATLAB Engine pointer in a Context.
        proxy::Context context{input_arguments, output_arguments, getEngine()};

        // Create a proxy::Factory.
        std::shared_ptr<proxy::Factory> proxy_factory = std::make_shared<CustomProxyFactory>();

        // Create an action::Factory.
        proxy::action::Factory action_factory{proxy_factory};

        // Create an Action.
        std::unique_ptr<proxy::action::Action> action = action_factory.makeAction(context);
        
        // Execute the Action.
        action->execute(context);
    }
};
