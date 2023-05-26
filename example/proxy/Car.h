#pragma once

#include "libmexclass/proxy/Proxy.h"
#include "libmexclass/proxy/method/Context.h"
#include "libmexclass/proxy/error/Result.h"

#include "../Car.h"

#include <variant>

namespace example::proxy {

class Car : public libmexclass::proxy::Proxy {
  public:
    Car(const std::string& make, const std::string& model, const std::string& color)
        : car{make, model, color} {
        
        // Step 1. Unpack constructor arguments.

        // Step 2. Initiliaze "raw" C++ object.
        // car = Car(make, model, color);

        // Step 3. Register methods.
        REGISTER_METHOD(Car, Accelerate);
        REGISTER_METHOD(Car, Decelerate);
        REGISTER_METHOD(Car, Stop);
        REGISTER_METHOD(Car, Headlights);
        REGISTER_METHOD(Car, SetSpeed);
        REGISTER_METHOD(Car, GetSpeed);
        REGISTER_METHOD(Car, GetMake);
        REGISTER_METHOD(Car, GetModel);
        REGISTER_METHOD(Car, GetColor);
        REGISTER_METHOD(Car, Print);
    }

    using MakeProxyResult = std::variant<std::shared_ptr<libmexclass::proxy::Proxy>, libmexclass::error::Error>;
    
    static libmexclass::error::Result<std::shared_ptr<libmexclass::proxy::Proxy>> make(const libmexclass::proxy::FunctionArguments& constructor_arguments);

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

    // Note: Clients can replace this with whatever "raw" C++ Class they want
    // to proxy method calls to.
    example::Car car;
};
} // namespace example::proxy
