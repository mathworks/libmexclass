#pragma once

#include "libmexclass/proxy/ID.h"
#include "libmexclass/proxy/ClassName.h"
#include "libmexclass/proxy/MethodName.h"
#include "libmexclass/proxy/FunctionArguments.h"

namespace libmexclass::action {

    struct CreateParameters {
        const ClassName class_name;
        const FunctionArguments constructor_arguments;
    };

    struct MethodCallParameters {
        const ID id;
        const MethodName method_name;
        const FunctionArguments method_arguments;
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
    
}
