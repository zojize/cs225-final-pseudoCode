#include "./Airline.h"

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
  size_t res = 17;
  res = res * 31 + hash<unsigned int>()(a.id);
  res = res * 31 + hash<string>()(a.name);
  return res;
}
