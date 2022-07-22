#include "mex.hpp"
#include "MatlabDataArray.hpp"

#include <string>

#include "Error.h"
#include "log/Level.h"

namespace libmexclass::error {
    Error::Error(std::shared_ptr<matlab::engine::MATLABEngine> matlab) {
        logger = libmexclass::log::Logger::getLogger(matlab);
    };

    void Error::error(const std::string& message) {
        logger->log(libmexclass::log::Level::Error, message);
    }

} // namespace libmexclass::log