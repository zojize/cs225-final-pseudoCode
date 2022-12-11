#include "./Airline.h"
#include "utils.h"

Airline::Airline(unsigned int id, std::string name) : id(id), name(name) {}

Airline::Airline(std::vector<std::string> const& entries)
    : Airline(std::stoi(entries[0]), entries[1]) {}

bool Airline::operator==(Airline const& other) const {
  return this == &other || (id == other.id && name == other.name);
}

std::ostream& operator<<(std::ostream& os, const Airline& a) {
  return os << "Airline { " << a.id << ", " << a.name << " }";
}

size_t std::hash<Airline>::operator()(const Airline& a) const {
  return static_cast<size_t>(a.id);
}
