#pragma once

#include <string>

namespace libmexclass::error {

    class Error {
    public:
        Error(const std::string& error_id, const std::string& error_message)
            : id_{error_id}
            , message_{error_message} {}

        const std::string& id() {
            return id_;
        }

        const std::string& message() {
            return message_;
        }

    private:
        std::string id_;
        std::string message_;
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
