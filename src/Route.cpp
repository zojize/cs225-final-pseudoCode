#include "Route.h"

Route::Route(std::vector<std::string> const& entries)
    : airline_id(std::stoi(entries[1])),
      source_airport_id(std::stoi(entries[3])),
      destination_airport_id(std::stoi(entries[5])) {}

std::ostream& operator<<(std::ostream& os, const Route& r) {
  return os << "Route { " << r.airline_id << ", " << r.source_airport_id << ", "
            << r.destination_airport_id << " }";
}
