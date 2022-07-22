#include "MatlabDataArray.hpp"

#include "proxy/ProxyManager.h"
#include "proxy/ID.h"

#include "Unsupported.h"

#include "MatlabDataArray.hpp"

namespace proxy {
    namespace action {

        void Unsupported::execute(Context& context) {
            context.error->error("The specified action is unsupported.");
            // matlab::data::ArrayFactory factory;
            // context.matlab->feval(u"error", 0,
            //                  std::vector<matlab::data::Array>({ factory.createScalar("The specified action is unsupported.") }));
        }

    } // namespace action
} // namespace proxy