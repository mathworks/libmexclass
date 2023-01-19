#include "Car.h"

#include <iostream>
namespace libmexclass::example {
void Car::Accelerate() {
    speed += Car::ACCELERATION_INCREMENT;
}

void Car::Decelerate() {
    speed -= Car::DECELERATION_INCREMENT;
}

void Car::Stop() {
    speed = 0;
}

void Car::SetSpeed(const std::uint64_t speed) {
    this->speed = speed;
}

void Car::Headlights(const bool state) {
    headlights = state;
}

const std::uint64_t Car::GetSpeed() const {
    return speed;
}

const std::string Car::GetMake() const {
    return make;
}

const std::string Car::GetModel() const {
    return model;
}

const std::string Car::GetColor() const {
    return color;
}

void Car::Print() const {
    std::cout << "Make: " << make << std::endl;
    std::cout << "Model: " << model << std::endl;
    std::cout << "Color: " << color << std::endl;
    std::cout << "Speed: " << speed << std::endl;
    std::cout << "Headlights: " << (headlights ? std::string("on") : std::string("off")) << std::endl;
}
} // namespace libmexclass::example
