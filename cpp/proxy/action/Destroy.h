#pragma once

#include "proxy/action/Action.h"

namespace proxy {
    namespace action {

        class Destroy : public Action {
            public:
            virtual ~Destroy() {}
            virtual void execute(Context& context) override;
        };

    } // namespace action
} // namespace proxy