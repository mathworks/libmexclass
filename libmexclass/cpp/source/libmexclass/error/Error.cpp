#include "libmexclass/error/Error.h"

namespace libmexclass::error {

    ErrorBuilder& ErrorBuilder::id(const string_t& error_id) {
        id_ = error_id;
        return *this;
    }

    ErrorBuilder& ErrorBuilder::message(const string_t& error_message) {
        message_ = error_message;
        return *this;
    }

    Error ErrorBuilder::build() const {
        return Error{id_, message_};
    }
}
