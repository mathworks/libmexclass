#pragma once

#include <memory>

#include "proxy/Factory.h"
#include "proxy/action/Action.h"

namespace proxy {
    namespace action {

        class Create : public Action {
            public:
                Create(std::shared_ptr<proxy::Factory> proxy_factory) : proxy_factory{proxy_factory} {
                    // TODO: Remove debug output.
                    std::cout << "Constructing 'Create' Action..." << std::endl;
                }
                virtual ~Create() {}
                virtual void execute(Context& context) override;
            private:
                std::shared_ptr<proxy::Factory> proxy_factory;
        };

    } // namespace action
} // namespace proxy