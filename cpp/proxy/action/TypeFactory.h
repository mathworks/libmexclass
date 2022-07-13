#pragma once

#include <string>

#include "proxy/action/Type.h"

namespace proxy {
    namespace action {
        class TypeFactory {
            public:
            Type make_type(const std::string& type_string);
            private:
            const std::string CREATE_STRING = "Create";
            const std::string METHOD_CALL_STRING = "MethodCall";
            const std::string DESTROY_STRING = "Destroy";
        };
    } // namespace action
} // namespace proxy