#pragma once

#include <iostream>
#include <string>
#include <vector>

struct Route {
  Route(unsigned int airline_id, unsigned int source_airport_id,
        unsigned int destination_airport_id);
  Route(std::vector<std::string> const& entries);

  unsigned int airline_id;
  unsigned int source_airport_id;
  unsigned int destination_airport_id;

  bool operator==(Route const& other) const;
};

std::ostream& operator<<(std::ostream& os, const Route& r);

template <>
struct std::hash<Route> {
  size_t operator()(const Route& ap) const;
};
