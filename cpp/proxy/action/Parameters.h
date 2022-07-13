#pragma once

#include "proxy/ID.h"
#include "proxy/ClassName.h"
#include "proxy/MethodName.h"

namespace proxy {
namespace action {

    struct CreateParameters {
        const ClassName class_name;
    };

    struct MethodCallParameters {
        const ID id;
        const MethodName method_name;
    };

    struct DestroyParameters {
        const ID id;
    };

    struct Parameters {
        // TODO: Make these optionals.
        const CreateParameters create_parameters{};
        const MethodCallParameters method_call_parameters{};
        const DestroyParameters destroy_parameters{};
    };
} // namespace action
} // namespace proxy