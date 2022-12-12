#include "libmexclass/action/TypeFactory.h"

// TODO: Remove
#include <iostream>

namespace libmexclass::action {

        Type TypeFactory::make_type(const std::string& type_string) const {
            if (type_string.compare(CREATE_STRING) == 0) {
                // TODO: Remove
                std::cout << "[LOG::INFO] action::Type == 'Create'" << std::endl; 
                return Type::Create;
            } else if (type_string.compare(METHOD_CALL_STRING) == 0) {
                // TODO: Remove
                std::cout << "[LOG::INFO] action::Type == 'MethodCall'" << std::endl; 
                return Type::MethodCall;
            } else if (type_string.compare(DESTROY_STRING) == 0) {
                // TODO: Remove
                std::cout << "[LOG::INFO] action::Type == 'Destroy'" << std::endl; 
                return Type::Destroy;
            }
            // TODO: Remove
            std::cout << "[LOG::INFO] action::Type == 'Unsupported'" << std::endl;
            return Type::Unsupported;
        }

}
