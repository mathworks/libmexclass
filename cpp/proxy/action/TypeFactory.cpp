#include "TypeFactory.h"

namespace proxy {
    namespace action {

        Type TypeFactory::make_type(const std::string& type_string) {
            if (type_string.compare(CREATE_STRING) == 0) {
                return Type::Create;
            } else if (type_string.compare(METHOD_CALL_STRING) == 0) {
                return Type::MethodCall;
            } else if (type_string.compare(DESTROY_STRING) == 0) {
                return Type::Destroy;
            }
            return Type::Unsupported;
        }

    } // namespace action
} // namespace proxy