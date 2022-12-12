#pragma once

#include "libmexclass/action/Type.h"

#include <string>

namespace libmexclass::action {

    class TypeFactory {
        public:
            Type make_type(const std::string& type_string) const;
        private:
            const std::string CREATE_STRING = "Create";
            const std::string METHOD_CALL_STRING = "MethodCall";
            const std::string DESTROY_STRING = "Destroy";
    };
    
}
