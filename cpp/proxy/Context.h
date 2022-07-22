#pragma once

#include <memory>

#include "mex.hpp"

#include "proxy/action/Parameters.h"
#include "proxy/action/Type.h"
#include "proxy/action/TypeFactory.h"
#include "MatlabDataArray.hpp"

#include "proxy/mex/Arguments.h"
#include "error/Error.h"

namespace proxy {
    class Context {
        public:
        
        Context(libmexclass::mex::Arguments& inputs, libmexclass::mex::Arguments& outputs, std::shared_ptr<matlab::engine::MATLABEngine> matlab) : inputs{inputs}, outputs{outputs}, matlab{matlab} {
            logger = std::make_shared<libmexclass::log::Logger>(matlab);
            error = std::make_shared<libmexclass::error::Error>(matlab);

            const auto first_arg = inputs[0];
            const auto first_arg_type = first_arg.getType();
            const auto first_arg_dimensions = first_arg.getDimensions();
            const auto rows = first_arg_dimensions[0];
            const auto columns = first_arg_dimensions[1];
            
            // Validate first argument type and size
            if (first_arg_type != matlab::data::ArrayType::MATLAB_STRING ||
                rows != 1 ||
                columns != 1) {
                error->error("The first argument must be a scalar string");
                // matlab::data::ArrayFactory factory;
                // matlab->feval(u"error", 0, std::vector<matlab::data::Array>({ factory.createScalar("The first argument must be a scalar string") }));
            }

            // Stub code that currently hardcodes any new context to use a "Create" action.
            // TODO: Convert inputs[0] to a std::string to dynamically create the appropriate action type.
            const std::string type_string = std::string{"Create"};

            action::TypeFactory type_factory;
            action_type = type_factory.make_type(type_string);
        }

        action::Type action_type;
        action::Parameters action_parameters;
        libmexclass::mex::Arguments& inputs;
        libmexclass::mex::Arguments& outputs;
        std::shared_ptr<matlab::engine::MATLABEngine> matlab;
        std::shared_ptr<libmexclass::error::Error> error;
        std::shared_ptr<libmexclass::log::Logger> logger;
    };
}