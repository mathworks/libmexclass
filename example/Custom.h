#pragma once

#include <string>

class Custom {
    public:
        void Print(const std::string& message) const;
        void IncrementState();
        std::string GetState();
    private:
        int state = 0;
};
