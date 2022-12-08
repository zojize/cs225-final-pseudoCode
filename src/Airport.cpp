#include "./Airport.h"
#include "utils.h"

Airport::Airport(unsigned int id, std::string name, double latitude,
                 double longitude)
    : id(id), name(name), latitude(latitude), longitude(longitude) {}

Airport::Airport(std::vector<std::string> const& entries)
    : Airport(std::stoi(entries[0]), entries[1], std::stod(entries[6]),
              std::stod(entries[7])) {}

bool Airport::operator==(Airport const& other) const {
  return this == &other ||
         (id == other.id && name == other.name && latitude == other.latitude &&
          longitude == other.longitude);
}

std::ostream& operator<<(std::ostream& os, Airport const& a) {
  return os << "Airport { " << a.id << ", " << a.name << ", " << a.latitude
            << ", " << a.longitude << " }";
}

bool Airport::operator<(Airport const& other) const {
  return (latitude < other.latitude && longitude < other.longitude);
}

size_t std::hash<Airport>::operator()(Airport const& a) const {
  size_t seed = 0;
  hash_combine(seed, a.id);
  hash_combine(seed, a.name);
  hash_combine(seed, a.latitude);
  hash_combine(seed, a.longitude);
  return seed;
}
