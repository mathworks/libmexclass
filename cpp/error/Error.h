#pragma once

#include "mex.hpp"
#include "MatlabDataArray.hpp"

#include <string>
#include <memory>

#include "log/Logger.h"

// TODO: Add a message catalog with error IDs
namespace libmexclass::error {
    class Error {
        private:
            // Pointer to instance of Logger
            std::shared_ptr<libmexclass::log::Logger> logger;

        public:
            Error(std::shared_ptr<matlab::engine::MATLABEngine> matlab);
            void error(const std::string& message);
    };

} // namespace libmexclass::log