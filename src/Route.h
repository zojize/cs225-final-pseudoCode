#pragma once

#include <string>
#include <vector>
#include <iostream>

struct Route {
  Route(std::vector<std::string> const& entries);
  unsigned int airline_id;
  unsigned int source_airport_id;
  unsigned int destination_airport_id;
};

std::ostream& operator<<(std::ostream& os, const Route& r);
