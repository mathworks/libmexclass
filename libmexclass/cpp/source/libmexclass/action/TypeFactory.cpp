#include "libmexclass/action/TypeFactory.h"

namespace libmexclass::action {

        Type TypeFactory::make_type(const std::string& type_string) const {
            if (type_string.compare(CREATE_STRING) == 0) {
                return Type::Create;
            } else if (type_string.compare(METHOD_CALL_STRING) == 0) {
                return Type::MethodCall;
            } else if (type_string.compare(DESTROY_STRING) == 0) {
                return Type::Destroy;
            }
            return Type::Unsupported;
        }

}
