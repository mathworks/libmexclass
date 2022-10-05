#pragma once

#include "mex.hpp"
#include "MatlabDataArray.hpp"

#include <string>
#include <memory>

#include "log/Level.h"

namespace libmexclass::log {
    class Logger {
        private:
            std::shared_ptr<matlab::engine::MATLABEngine> matlab;
            matlab::data::ArrayFactory factory;

            // static singleton instance of Logger
            static inline std::shared_ptr<Logger> instance = nullptr;

            Logger(std::shared_ptr<matlab::engine::MATLABEngine> matlab) : matlab{matlab}, factory{} {};

        public:
            // TODO: Why can't the constructor be private?

            static std::shared_ptr<Logger> getLogger(std::shared_ptr<matlab::engine::MATLABEngine> matlab);
            void log(const log::Level level, const std::string& message);
    };

} // namespace libmexclass::log