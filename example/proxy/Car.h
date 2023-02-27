#pragma once

#include "libmexclass/proxy/Proxy.h"
#include "libmexclass/proxy/method/Context.h"

#include "../Car.h"

namespace example::proxy {
class Car : public libmexclass::proxy::Proxy {
  public:
    Car(const libmexclass::proxy::FunctionArguments& constructor_arguments)
        : car{convert(constructor_arguments, 0), convert(constructor_arguments, 1), convert(constructor_arguments, 2)} {
        // Step 1. Unpack constructor arguments.

        // Step 2. Initiliaze "raw" C++ object.
        // car = Car(make, model, color);

        // Step 3. Register methods.
        registerMethod(Car, Accelerate);
        registerMethod(Car, Decelerate);
        registerMethod(Car, Stop);
        registerMethod(Car, Headlights);
        registerMethod(Car, SetSpeed);
        registerMethod(Car, GetSpeed);
        registerMethod(Car, GetMake);
        registerMethod(Car, GetModel);
        registerMethod(Car, GetColor);
        registerMethod(Car, Print);
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
        return std::string(mda[0]);
    }

    // Note: Clients can replace this with whatever "raw" C++ Class they want
    // to proxy method calls to.
    example::Car car;
};
} // namespace example::proxy
