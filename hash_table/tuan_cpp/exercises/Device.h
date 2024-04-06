#ifndef DEVICE_H_INCLUDED
#define DEVICE_H_INCLUDED

#include <iostream>

class Device {
public:
  std::string name = "";
  std::string company = "";
  float price = 0.0;

  Device() = default;
  Device(std::string n, std::string c, float p): name{n}, company{c}, price{p} {};

  void print() {
    std::cout << name << ", " << company << ", " << price;
  };
};

#endif // DEVICE_H_INCLUDED
