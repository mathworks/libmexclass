#pragma once

namespace proxy {
    namespace action {
        enum class Type {
            Create,
            MethodCall,
            Destroy,
            Unsupported
        };
    } // namespace action
} // namespace proxy