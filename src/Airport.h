#pragma once

#include <iostream>
#include <string>
#include <vector>

struct Airport {
  Airport(unsigned int id, std::string name, double latitude, double longitude);
  Airport(std::vector<std::string> const& entries);

  unsigned int id;
  std::string name;
  double latitude;
  double longitude;
  
  bool operator==(Airport const& other) const;
};

std::ostream& operator<<(std::ostream& os, const Airport&);

// https://stackoverflow.com/a/17017281/14835397
template <>
struct std::hash<Airport> {
  size_t operator()(const Airport& ap) const;
};
