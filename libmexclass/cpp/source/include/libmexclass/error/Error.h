#pragma once

#include <string>

namespace libmexclass::error {

    using string_t = std::basic_string<char16_t>;

    struct Error {
        const string_t id;
        const string_t msg;
    };

    class ErrorBuilder {
    public:
        ErrorBuilder& id(const string_t& error_id);

        ErrorBuilder& message(const string_t& error_message);

        Error build() const;

    private:
        string_t id_;
        string_t message_;
    }
}
