#pragma once

#include <iostream>
#include <string>
#include <vector>

struct Airline {
  Airline(unsigned int id, std::string name);
  Airline(std::vector<std::string> const& entries);

  unsigned int id;
  std::string name;

  bool operator==(Airline const& other) const;
};

std::ostream& operator<<(std::ostream& os, const Airline&);

// https://stackoverflow.com/a/17017281/14835397
template <>
struct std::hash<Airline> {
  size_t operator()(const Airline&) const;
};

