#include "Car.h"

#include "MatlabDataArray.hpp"

namespace example::proxy {
void Car::Accelerate(libmexclass::proxy::method::Context& context) {
    // car.Acclerate does not take any input arguments
    car.Accelerate();
}

void Car::Decelerate(libmexclass::proxy::method::Context& context) {
    // car.Decelerate does not take any input arguments
    car.Decelerate();
}

void Car::Stop(libmexclass::proxy::method::Context& context) {
    // car.Stop does not take any input arguments
    car.Stop();
}

void Car::Headlights(libmexclass::proxy::method::Context& context) {
    // First, cast the first cell array element into a MDA TypedArray<bool> array.
    matlab::data::TypedArray<bool> state_mda = context.inputs[0];
    // Second, extract the first [0th] element from the MDA TypedArray and convert it into a boolean value.
    const bool state = bool(state_mda[0]);
    // Third, pass the unwrapped native C++ boolean value to the raw C++ object Headlights() method.
    car.Headlights(state);
}

void Car::GetSpeed(libmexclass::proxy::method::Context& context) {
    // First, get speed from Car class.
    const uint64_t speed = car.GetSpeed();

    // Return the state value from C++ to MATLAB.
    matlab::data::ArrayFactory factory;
    auto speed_mda = factory.createScalar(speed);
    context.outputs[0] = speed_mda;
}

void Car::SetSpeed(libmexclass::proxy::method::Context& context) {
    // First, cast the first cell array element into a MDA TypedArray<uint64_t> array.
    matlab::data::TypedArray<uint64_t> speed_mda = context.inputs[0];
    // Second, extract the first [0th] element from the MDA TypedArray and convert it into a uint64_t value.
    const std::uint64_t speed = uint64_t(state_mda[0]);
    if (speed > 100) {
        context.error = libmexclass::error::Error{"Car:Speed:TooFast", "Slow down!!"};
        return;
    }
    
    
    // Third, pass the unwrapped native C++ int64_t value to the raw C++ object Headlights() method.
    car.SetSpeed(speed);
}

void Car::GetMake(libmexclass::proxy::method::Context& context) {
    // First, get make from Car class.
    const std::string make = car.GetMake();

    // Return the state value from C++ to MATLAB.
    matlab::data::ArrayFactory factory;
    auto make_mda = factory.createScalar(make);
    context.outputs[0] = make_mda;
}

void Car::GetModel(libmexclass::proxy::method::Context& context) {
    // First, get model from Car class.
    const std::string model = car.GetModel();

    // Return the state value from C++ to MATLAB.
    matlab::data::ArrayFactory factory;
    auto model_mda = factory.createScalar(model);
    context.outputs[0] = model_mda;
}

void Car::GetColor(libmexclass::proxy::method::Context& context) {
    // First, get color from Car class.
    const std::string color = car.GetColor();

    // Return the state value from C++ to MATLAB.
    matlab::data::ArrayFactory factory;
    auto color_mda = factory.createScalar(color);
    context.outputs[0] = color_mda;
}

void Car::Print(libmexclass::proxy::method::Context& context) {
    car.Print();
}
} // namespace example::proxy
