#pragma once

#define _USE_MATH_DEFINES
#define EPSILON 1e-6

#include "Airport.h"
#include "Graph.h"
#include "Route.h"

#include <cmath>
#include <string>
#include <unordered_map>
#include <vector>

template <typename T>
T checked_stoi(std::string const& s) {
  if (s != "\\N")
    return std::stoi(s);
  throw std::domain_error("wait... this is not a number!");
}

// apparently inline fixes dup symbol error for whatever reason...
// formula from http://edwilliams.org/gccalc.htm
// uses spherical earth model
// returns distance in km (may change)
inline double geo_distance(Airport const& source, Airport const& destination) {
  double to_radian = M_PI / 180;
  double lat1 = source.latitude * to_radian;
  double lon1 = source.longitude * to_radian;
  double lat2 = destination.latitude * to_radian;
  double lon2 = destination.longitude * to_radian;

  return acos(sin(lat1) * sin(lat2) + cos(lat1) * cos(lat2) * cos(lon1 - lon2))
         /* convert to physical may be unnecessary */
         * (180. / M_PI) * 60 * 1.852;
}

// https://stackoverflow.com/a/8319960/14835397
template <typename T>
inline void hash_combine(std::size_t& seed, T const& v) {
  seed ^= std::hash<T>()(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

template <typename T>
inline bool approx_eq(T const& L, T const& R) {
  return std::abs(L - R) < T(EPSILON);
}

inline void build_graph(Graph<Airport>& g, std::vector<Airport> const& airports,
                        std::vector<Route> const& routes) {
  std::unordered_map<unsigned int, size_t> m_airports;

  for (size_t i = 0; i < airports.size(); i++)
    m_airports[airports[i].id] = i;

  for (auto a : airports) {
    g.add_vertex(a);
  }

  for (auto r : routes) {
    auto source = airports[m_airports[r.source_airport_id]];
    auto destination = airports[m_airports[r.destination_airport_id]];
    double distance = geo_distance(source, destination);
    if (source.id == 2965 && destination.id == 2990)
      std::cout << "building : " << source << ", " << destination << ", "
                << distance << std::endl;
    g.add_edge(source, destination, distance);
  }
}
