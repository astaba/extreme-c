// File name: ExtremeC_examples_chapter6_2_main.cpp
// Description: Main function
#include "ExtremeC_examples_chapter6_2.h"
#include <iostream>

// Main function
int main(int argc, char **argv) {
  // Create the object variable and call the constructor
  Car car("Renault");

  // Main algorithm
  car.Refuel(100.0);
  std::cout << "Car is refueled, the correct fuel level is " << car.fuel
            << std::endl;

  while (car.fuel > 0) {
    std::cout << "Car fuel level: " << car.fuel << std::endl;
    if (car.speed < 80) {
      car.Accelerate();
      std::cout << "Car has been accelerated to the speed: " << car.speed
                << std::endl;
    } else {
      car.Brake();
      std::cout << "Car has been slowed down to the speed: " << car.speed
                << std::endl;
    }
  }
  std::cout << "Car ran out of the fuel! Slowing down ..." << std::endl;

  while (car.speed > 0) {
    car.Brake();
    std::cout << "Car has been slowed down to the speed: " << car.speed
              << std::endl;
  }

  std::cout << "Car is stopped!" << std::endl;
  // When leaving the function, the object 'car' gets
  // destructed automatically.
  return 0;
}
