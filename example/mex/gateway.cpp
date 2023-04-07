#include "mex.hpp"
#include "mexAdapter.hpp"

#include "libmexclass/mex/gateway.h"

#include "CarProxyFactory.h"

class MexFunction : public matlab::mex::Function {
    public:
        void operator()(matlab::mex::ArgumentList outputs, matlab::mex::ArgumentList inputs) {
            libmexclass::mex::gateway<CarProxyFactory>(inputs, outputs, getEngine());
        }
};
