#pragma once

#include <string>
#include <vector>
#include <iostream>

struct Airport {
  Airport(std::vector<std::string> const& entries);
  unsigned int id;
  std::string name;
  double latitude;
  double longitude;
};

std::ostream& operator<<(std::ostream& os, const Airport& ap);
