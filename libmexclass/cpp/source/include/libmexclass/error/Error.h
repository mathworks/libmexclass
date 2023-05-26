#pragma once

#include <string>

namespace libmexclass::error {
    struct Error {
        const std::string id;
        const std::string message;
    };

    class ErrorBuilder {
    public:
        ErrorBuilder& id(const std::string& error_id);

        ErrorBuilder& message(const std::string& error_message);

        Error build() const;

    private:
        std::string id_;
        std::string message_;
    };
}