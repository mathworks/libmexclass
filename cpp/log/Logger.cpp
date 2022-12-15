#include "mex.hpp"
#include "MatlabDataArray.hpp"

#include <string>

#include "Logger.h"

namespace libmexclass::log {

    std::shared_ptr<Logger> Logger::getLogger(std::shared_ptr<matlab::engine::MATLABEngine> matlab) {
        if (!instance) {
            std::shared_ptr<Logger> instance(new Logger(matlab));
            return instance;
        }
        return instance;
    }

    void Logger::log(const Level level, const std::string& message) {
        switch (level) {
        case Level::Log:
            matlab->feval(u"disp", 0, std::vector<matlab::data::Array>({ 
                factory.createScalar(message) }));
                break;
        case Level::Warning:
            matlab->feval(u"warning", 0, std::vector<matlab::data::Array>({ 
                factory.createScalar(message) }));
                break;
        case Level::Error:
            matlab->feval(u"error", 0, std::vector<matlab::data::Array>({ 
                factory.createScalar(message) }));
                break;
        default:
            matlab->feval(u"error", 0, std::vector<matlab::data::Array>({ 
                factory.createScalar("Unrecognized log level.") }));

        }
    }

} // namespace libmexclass::log