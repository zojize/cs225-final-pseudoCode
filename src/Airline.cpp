#include "./Airline.h"

Airline::Airline(std::vector<std::string> const& entries)
    : id(std::stoi(entries[0])), name(entries[1]) {}

std::ostream& operator<<(std::ostream& os, const Airline& al) {
  return os << "Airline { " << al.id << ", " << al.name << " }";
}
