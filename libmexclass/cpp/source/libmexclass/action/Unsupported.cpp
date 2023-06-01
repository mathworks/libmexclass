#include "libmexclass/action/Unsupported.h"

#include "MatlabDataArray.hpp"

namespace libmexclass::action {

        std::optional<libmexclass::error::Error> Unsupported::execute() {
            return libmexclass::error::Error{"libmexclass:action:UnsupportedAction", "The specified action is unsupported"};
        }
}
