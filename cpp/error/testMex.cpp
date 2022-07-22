#include "mex.hpp"
#include "mexAdapter.hpp"

#include <string>

#include "error/Error.h"

class MexFunction : public matlab::mex::Function {
    public:
        void operator()(matlab::mex::ArgumentList outputs, matlab::mex::ArgumentList inputs) {

            std::shared_ptr<libmexclass::error::Error> error = std::make_shared<libmexclass::error::Error>(getEngine());

            error->error("test error using logger");
        }
};