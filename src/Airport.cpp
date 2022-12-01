#include "./Airport.h"

Airport::Airport(unsigned int id, std::string name, double latitude,
                 double longitude)
    : id(id), name(name), latitude(latitude), longitude(longitude) {}

Airport::Airport(std::vector<std::string> const& entries)
    : Airport(std::stoi(entries[0]), entries[0], std::stod(entries[6]),
              std::stod(entries[7])) {}

bool Airport::operator==(Airport const& other) const {
  return this == &other ||
         (id == other.id && name == other.name && latitude == other.latitude &&
          longitude == other.longitude);
}

std::ostream& operator<<(std::ostream& os, const Airport& a) {
  return os << "Airport { " << a.id << ", " << a.name << ", " << a.latitude
            << ", " << a.longitude << " }";
}

size_t std::hash<Airport>::operator()(const Airport& a) const {
  size_t res = 17;
  res = res * 31 + hash<unsigned int>()(a.id);
  res = res * 31 + hash<string>()(a.name);
  res = res * 31 + hash<double>()(a.latitude);
  res = res * 31 + hash<double>()(a.longitude);
  return res;
}
