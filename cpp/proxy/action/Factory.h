#pragma once

#include <memory>

#include "MatlabDataArray.hpp"

#include "proxy/action/Action.h"
#include "proxy/action/Create.h"
#include "proxy/action/Destroy.h"
#include "proxy/action/MethodCall.h"
#include "proxy/action/Unsupported.h"

namespace proxy {
    namespace action {

        class Factory {
            public:
            Factory(std::shared_ptr<proxy::Factory> proxy_factory) : proxy_factory{proxy_factory} {

            }
            std::unique_ptr<Action> makeAction(proxy::Context& context) {
                switch (context.action_type) {
                    case Type::Create:
                        return std::make_unique<Create>(proxy_factory);
                        break;
                    case Type::Destroy:
                        return std::make_unique<Destroy>();
                        break;
                    case Type::MethodCall:
                        return std::make_unique<MethodCall>();
                        break;
                    default: // Type::Unsupported
                        return std::make_unique<Unsupported>();
                }
            }

            private:
            std::shared_ptr<proxy::Factory> proxy_factory;

        };


    } // namespace action
} // namespace proxy