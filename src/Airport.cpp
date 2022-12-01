#include "./Airport.h"

Airport::Airport(std::vector<std::string> const& entries)
    : id(std::stoi(entries[0])), name(entries[0]),
      latitude(std::stod(entries[6])), longitude(std::stod(entries[6])) {}

std::ostream& operator<<(std::ostream& os, const Airport& ap) {
  return os << "Airport { " << ap.id << ", " << ap.name << ", " << ap.latitude
            << ", " << ap.longitude << " }";
}
