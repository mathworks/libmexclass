#include "Custom.h"

#include <iostream>

void Custom::Print(const std::string& message) const {
    std::cout << "Message: " << message << std::endl;
}

void Custom::IncrementState() {
    state += 1;
}

std::string Custom::GetState() {
    return std::to_string(state);
}
