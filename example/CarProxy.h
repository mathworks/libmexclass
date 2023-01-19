#pragma once

#include "libmexclass/proxy/Proxy.h"
#include "libmexclass/proxy/method/Context.h"

#include "Car.h"

class CarProxy : public libmexclass::proxy::Proxy {
  public:
    CarProxy(const libmexclass::proxy::FunctionArguments& constructor_arguments)
        : car{convert(constructor_arguments, 0), convert(constructor_arguments, 1), convert(constructor_arguments, 2)} {
        // Step 1. Unpack constructor arguments.

        // Step 2. Initiliaze "raw" C++ object.
        // car = Car(make, model, color);

        // Step 3. Register methods.
        registerMethod(CarProxy, Accelerate);
        registerMethod(CarProxy, Decelerate);
        registerMethod(CarProxy, Stop);
        registerMethod(CarProxy, Headlights);
        registerMethod(CarProxy, SetSpeed);
        registerMethod(CarProxy, GetSpeed);
        registerMethod(CarProxy, GetMake);
        registerMethod(CarProxy, GetModel);
        registerMethod(CarProxy, GetColor);
        registerMethod(CarProxy, Print);
    }

  private:
    void Accelerate(libmexclass::proxy::method::Context& context);
    void Decelerate(libmexclass::proxy::method::Context& context);
    void Stop(libmexclass::proxy::method::Context& context);
    void Headlights(libmexclass::proxy::method::Context& context);
    void SetSpeed(libmexclass::proxy::method::Context& context);
    void GetSpeed(libmexclass::proxy::method::Context& context);
    void GetMake(libmexclass::proxy::method::Context& context);
    void GetModel(libmexclass::proxy::method::Context& context);
    void GetColor(libmexclass::proxy::method::Context& context);
    void Print(libmexclass::proxy::method::Context& context);

    std::string convert(const libmexclass::proxy::FunctionArguments& constructor_arguments, std::uint64_t index) const {
        matlab::data::StringArray mda = constructor_arguments[index];
        const std::string result = std::string(mda[0]);
        return result;
    }

    // Note: Clients can replace this with whatever "raw" C++ Class they want
    // to proxy method calls to.
    Car car;
};
