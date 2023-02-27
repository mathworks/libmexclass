#pragma once

#include <string>

namespace example {
class Car {

  public:
    // Constructor
    Car(const std::string& make, const std::string& model, const std::string& color)
        : make{make}
        , model{model}
        , color{color} {}

    // Actions
    void Accelerate();
    void Decelerate();
    void Stop();
    void Headlights(const bool state);

    // Setters
    void SetSpeed(const std::uint64_t mph);

    // Getters
    const std::uint64_t GetSpeed() const;
    const std::string GetMake() const;
    const std::string GetModel() const;
    const std::string GetColor() const;

    // Logging
    void Print() const;

  private:
    // Mutable state
    std::uint64_t speed = 0;
    bool headlights = false;

    // Immutable state
    const std::string make;
    const std::string model;
    const std::string color;

    // Static Constants
    const static inline std::uint64_t ACCELERATION_INCREMENT = 10;
    const static inline std::uint64_t DECELERATION_INCREMENT = 5;
};
} // namespace example
