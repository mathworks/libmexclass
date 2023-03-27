#include "mex.hpp"
#include "mexAdapter.hpp"

#include <iostream>

class MexFunction : public matlab::mex::Function {
    public:
        void operator()(matlab::mex::ArgumentList outputs, matlab::mex::ArgumentList inputs) {
            std::cout << "test" << std::endl;
        }
};
