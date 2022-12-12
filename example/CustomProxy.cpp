#include "CustomProxy.h"

#include "MatlabDataArray.hpp"

void CustomProxy::Print(libmexclass::proxy::method::Context& context) {
    // First, cast the first cell array element into a MDA String array.
    matlab::data::StringArray message_mda = context.inputs[0];
    // Second, extract the first [0th] element from the MDA String Array and convert it into a std::string.
    const std::string message = std::string(message_mda[0]);
    // Third, pass the unwrapped native C++ std::string value to the raw C++ object Print() method.
    custom.Print(message);
}

void CustomProxy::Foo(libmexclass::proxy::method::Context& context) {
    custom.IncrementState();
    // Second, extract the first [0th] element from the MDA String Array and convert it into a std::string.
    const std::string message = "State = " + custom.GetState();
    // Third, pass the unwrapped native C++ std::string value to the raw C++ object Print() method.
    custom.Print(message);

    // Return the state value from C++ to MATLAB.
    // In this case, we are assigning multiple outputs.
    matlab::data::ArrayFactory factory;
    auto s = factory.createScalar(message);
    context.outputs[0] = s;
}
