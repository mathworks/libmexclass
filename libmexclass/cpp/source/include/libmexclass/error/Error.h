#pragma once

#include <string>

namespace libmexclass::error {
    struct Error {
        const string_t id;
        const string_t msg;
    };

    class ErrorBuilder {
    public:
        ErrorBuilder& id(const std::string& error_id);

        ErrorBuilder& message(const std::string& error_message);

        Error build() const;

    private:
        string_t id_;
        string_t message_;
    };
}
