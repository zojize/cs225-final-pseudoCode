#pragma once

#define _USE_MATH_DEFINES
#define EPSILON 1e-6

#include "Airport.h"
#include "CsvReader.h"
#include "Graph.h"
#include "Route.h"
#include "SvgCanvas.h"
#include "Vector2d.h"

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
static double to_radian = M_PI / 180;
inline double geo_distance(Airport const& source, Airport const& destination) {
  double lat1 = source.latitude * to_radian;
  double lon1 = source.longitude * to_radian;
  double lat2 = destination.latitude * to_radian;
  double lon2 = destination.longitude * to_radian;

  return acos(sin(lat1) * sin(lat2) + cos(lat1) * cos(lat2) * cos(lon1 - lon2))
         /* converting to physical unit may be unnecessary */
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

inline void load_data(std::vector<Airport>& airports,
                      std::string const& airports_fname,
                      std::vector<Route>& routes,
                      std::string const& routes_fname) {
  for (auto a : CsvReader(airports_fname)) {
    airports.push_back(Airport{a});
  }

  for (auto r : CsvReader(routes_fname)) {
    try {
      routes.push_back(Route{r});
    } catch (std::exception const& e) {
      // invalid routes are ignored
    }
  }
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
    g.add_edge(source, destination, distance);
  }
}

// https://github.com/blaurt/map-app-v1/blob/master/js/main.js
inline Vector2d<double> lat_lon_to_offsets(double lat, double lon,
                                           int map_width, int map_height) {
  static double FE = 180;
  double radius = map_width / (2 * M_PI);
  double lat_rad = lat * to_radian;
  double lon_rad = (lon + FE) * to_radian;

  double x = lon_rad * radius;
  double y_from_equator = radius * std::log(std::tan(M_PI_4 + lat_rad / 2));
  double y = map_height / 2 - y_from_equator;

  if (x < 0)
    x += map_width;
  if (y < 0)
    y += map_height;

  return {x, y};
}

inline Vector2d<double> bezier_handler(Vector2d<double> const& vl,
                                       Vector2d<double> const& vr) {

  static Vector2d<double> RIGHT{1, 0};
  auto diff = vr - vl;
  auto mag = diff.magnitude();
  auto dir = diff.clone().normalize();
  // dir *= std::pow(dir.dot(RIGHT), 2) * sqrt(mag);
  dir *= dir.dot(RIGHT) * sqrt(mag);
  // yep, this totally feels right to me
  auto h1 = vl + dir.rotate(-M_PI_2) * 4;
  auto h2 = h1 + diff;
  return (h1 + h1 + diff) / 2;
}

inline void draw_route(SvgCanvas& canvas, Airport const& source,
                       Airport const& dest) {
  auto w = canvas.width, h = canvas.height;

  auto vl = lat_lon_to_offsets(source.latitude, source.longitude, w, h);
  auto vr = lat_lon_to_offsets(dest.latitude, dest.longitude, w, h);

  if (vl.x > vr.x)
    std::swap(vl, vr);

  auto v_overl = Vector2d(-w + vr.x, vr.y);
  auto v_overr = Vector2d(w + vl.x, vl.y);

  auto dist = vl.dist(vr);
  auto dist_l = vl.dist(v_overl);

  auto dist_min = std::min(dist, dist_l);

  if (dist_min == dist) {
    auto mid = bezier_handler(vl, vr);
    canvas.quadratic_bezier(vl.x, vl.y, mid.x, mid.y, vr.x, vr.y);
  } else {
    auto midl = bezier_handler(v_overl, vl);
    auto midr = bezier_handler(vr, v_overr);
    canvas.quadratic_bezier(vl.x, vl.y, midl.x, midl.y, v_overl.x, v_overl.y)
        .quadratic_bezier(vr.x, vr.y, midr.x, midr.y, v_overr.x, v_overr.y);
  }
}

inline std::string lowercase(std::string const& s) {
  std::string s1(s);
  for (char& c : s1)
    c = tolower(c);
  return s1;
}
