#include "Route.h"
#include "utils.h"

Route::Route(unsigned int airline_id, unsigned int source_airport_id,
             unsigned int destination_airport_id)
    : airline_id(airline_id), source_airport_id(source_airport_id),
      destination_airport_id(destination_airport_id) {}

Route::Route(std::vector<std::string> const& entries)
    : Route(checked_stoi<unsigned int>(entries[1]),
            checked_stoi<unsigned int>(entries[3]),
            checked_stoi<unsigned int>(entries[5])) {}

bool Route::operator==(Route const& other) const {
  return this == &other ||
         (airline_id == other.airline_id &&
          source_airport_id == other.source_airport_id &&
          destination_airport_id == other.destination_airport_id);
}

std::ostream& operator<<(std::ostream& os, const Route& r) {
  return os << "Route { " << r.airline_id << ", " << r.source_airport_id << ", "
            << r.destination_airport_id << " }";
}

size_t std::hash<Route>::operator()(const Route& r) const {
  size_t seed = 0;
  hash_combine(seed, r.airline_id);
  hash_combine(seed, r.source_airport_id);
  hash_combine(seed, r.destination_airport_id);
  return seed;
}
