#include "mex.hpp"
#include "mexAdapter.hpp"

#include <string>

#include "log/Logger.h"
#include "log/Level.h"

class MexFunction : public matlab::mex::Function {
    public:
        void operator()(matlab::mex::ArgumentList outputs, matlab::mex::ArgumentList inputs) {

            std::shared_ptr<libmexclass::log::Logger> logger = libmexclass::log::Logger::getLogger(getEngine());

            logger->log(libmexclass::log::Level::Log, "test logging");
            logger->log(libmexclass::log::Level::Warning, "test warning");
            logger->log(libmexclass::log::Level::Error, "test error");
        }
};