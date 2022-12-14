#pragma once

#include <iostream>
#include <string>
#include <vector>

struct Airport {
  Airport() = default;
  Airport(unsigned int id, std::string const& name, std::string const& iata,
          std::string const& icao, double latitude, double longitude);
  Airport(std::vector<std::string> const& entries);

  unsigned int id;
  std::string name;
  std::string iata;
  std::string icao;
  double latitude;
  double longitude;

  bool operator==(Airport const& other) const;
  bool operator!=(Airport const& other) const;
  bool operator<(Airport const& other) const;
  double operator-(Airport const& other) const;
};

std::ostream& operator<<(std::ostream& os, Airport const&);

// https://stackoverflow.com/a/17017281/14835397
template <>
struct std::hash<Airport> {
  size_t operator()(Airport const& ap) const;
};
