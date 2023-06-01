#pragma once

#include <string>

namespace libmexclass::error {
    struct Error {
        const std::string id;
        const std::string message;
        
        Error(const std::string& error_id, const std::string& error_message)
            : id{error_id}
            , message{error_message} {}
        
        Error(const Error& error)
            : id{error.id}
            , message{error.message} {}
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
