#pragma once

#include <iostream>
#include <string>
#include <vector>

struct Airline {
  Airline(std::vector<std::string> const& entries);
  unsigned int id;
  std::string name;
};

std::ostream& operator<<(std::ostream& os, const Airline& al);
