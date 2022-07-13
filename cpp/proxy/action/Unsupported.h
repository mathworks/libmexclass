#pragma once

#include "proxy/action/Action.h"

namespace proxy {
    namespace action {

        class Unsupported : public Action {
            public:
                virtual ~Unsupported() {}
                virtual void execute(Context& context);
        };

    } // namespace action
} // namespace proxy