#include "Airport.h"
#include "Algorithms.h"
#include "Canvas.h"
#include "SvgCanvas.h"
#include "Vector2d.h"
#include "cs225/PNG.h"
#include "utils.h"

#include "getopt.h"
#include <iostream>

using namespace std;

// clang-format off
static string usage_prompt = \
  "Finds the shortest path between airports using either A* or Dijkstra's algorithm.\n\n"
  "USAGE: ./main [OPTIONS] SOURCE_AIRPORT DESTINATION_AIRPORT\n\n"
  "POSITIONAL ARGUMENTS:\n"
  "    SOURCE_AIRPORT       Airport code of the source airport.\n"
  "    DESTINATION_AIRPORT  Airport code of the destination airport.\n\n"
  "OPTIONS:\n"
  "    -h, --help\n"
  "                         Show this message and exit.\n"
  "    -m, --mode [=text]\n"
  "                         Select the output mode. Valid options are \"text\" for a\n"
  "                         list of airports to get to the destination and \"svg\"\n"
  "                         to output the visualized routes to a svg file.\n"
  "    -a, --algorithm [=dijkstra]\n"
  "                         Select the algorithm to use for pathfinding. Valid options\n"
  "                         are \"A*\" for A* search and \"dijkstra\" for Dijkstra's.\n"
  "    -o, --out [=output.svg]\n"
  "                         Name for the output svg."
  "    --routes [=../data/routes.csv]\n"
  "                         Dataset csv filename for routes."
  "    --airports [=../data/airports.csv]\n"
  "                         Dataset csv filename for airports."
  "    --map [=../data/map.png]\n"
  "                         World map image file, has to be png."
  ;
// clang-format on

static string mode = "text";
static string algorithm = "dijkstra";
static string outfile = "output.svg";
static string routes_fname = "../data/routes.csv";
static string airports_fname = "../data/airports.csv";
static string map_fname = "../data/map.png";

void process_args(int argc, char **argv) {
  char const *const short_opts = "m:a:o:h";
  const option long_opts[] = {{"mode", required_argument, nullptr, 'm'},
                              {"algorithm", required_argument, nullptr, 'a'},
                              {"out", required_argument, nullptr, 'o'},
                              {"help", no_argument, nullptr, 'h'},
                              {"routes", required_argument, nullptr, 'r'},
                              {"airports", required_argument, nullptr, 'p'},
                              {"help", required_argument, nullptr, 'h'},
                              {"map", required_argument, nullptr, 'i'},
                              {nullptr, no_argument, nullptr, 0}};
  int opt;
  while ((opt = getopt_long(argc, argv, short_opts, long_opts, nullptr)) !=
         -1) {

    switch (opt) {
    case 'a':
      algorithm = optarg;
      algorithm = lowercase(algorithm);
      if (!(algorithm == "dijkstra" || algorithm == "a*")) {
        cerr << "Invalid algorithm " << algorithm << endl;
        exit(1);
      }
      break;
    case 'o':
      outfile = optarg;
      break;
    case 'm':
      mode = optarg;
      mode = lowercase(mode);
      if (!(mode == "text" || mode == "svg")) {
        cerr << "Invalid mode " << mode << endl;
        exit(1);
      }
      break;
    case 'i':
      map_fname = optarg;
      break;
    case 'r':
      routes_fname = optarg;
      break;
    case 'p':
      airports_fname = optarg;
      break;
    case 'h':
    case '?':
    default:
      cout << usage_prompt << endl;
      exit(0);
    }
  }
}

int main(int argc, char *argv[]) {
  process_args(argc, argv);

  if (argc == 1) {
    cout << usage_prompt << endl;
    return 0;
  }

  if (argc - optind < 2) {
    cerr << "Must provide both SOURCE_AIRPORT and DESTINATION_AIRPORT.";
    return 1;
  }

  string source = argv[optind];
  source = lowercase(source);
  string dest = argv[optind + 1];
  dest = lowercase(dest);

  vector<Airport> airports;
  vector<Route> routes;

  load_data(airports, airports_fname, routes, routes_fname);

  unordered_map<string, size_t> m_airports;

  for (size_t i = 0; i < airports.size(); i++) {
    Airport& a = airports[i];
    m_airports[to_string(a.id)] = i;
    if (a.iata != "\\N")
      m_airports[lowercase(a.iata)] = i;
    m_airports[lowercase(a.icao)] = i;
  }

  if (m_airports.find(source) == m_airports.end()) {
    cerr << "SOURCE_AIRPORT " << source << " not found." << endl;
    return 1;
  }
  if (m_airports.find(dest) == m_airports.end()) {
    cerr << "DESTINATION_AIRPORT " << dest << " not found." << endl;
    return 1;
  }

  Airport const& source_airport = airports[m_airports[source]];
  Airport const& dest_airport = airports[m_airports[dest]];

  Graph<Airport> g;
  cout << "Building Graph<Airport>..." << endl;
  build_graph(g, airports, routes);
  cout << "Finished building Graph<Airport>" << endl;

  cout << "Running " << algorithm << "..." << endl;
  vector<Airport> search_result;
  search_result = algorithm == "dijkstra"
                      ? Algorithms::find_shortest_path_dijkstra(
                            g, source_airport, dest_airport)
                      : Algorithms::find_shortest_path_A_star(g, source_airport,
                                                              dest_airport);
  cout << "Finished running " << algorithm << endl;

  if (mode == "text") {
    if (search_result.size() == 0) {
      cout << "No viable path found for " << source << " and " << dest << "."
           << endl;
    }

    for (size_t i = 0; i < search_result.size() - 1; i++)
      cout << search_result[i].name << " ->" << endl;
    cout << search_result.back().name << endl;
    return 0;
  }

  cs225::PNG map;
  map.readFromFile(map_fname);

  SvgCanvas canvas(map.width(), map.height());
  canvas.image(map_fname);

  canvas.attrs["fill"] = "rgb(255, 255, 255)";
  canvas.attrs["stroke"] = "rgb(0, 0, 0)";
  for (size_t i = 0; i < search_result.size(); i++) {
    Airport const& a = search_result[i];
    Vector2d<double> p = lat_lon_to_offsets(a.latitude, a.longitude,
                                            canvas.width, canvas.height);
    canvas.circle(p.x, p.y, 3);
  }

  canvas.attrs["stroke"] = "rgba(255, 0, 0, 0.3)";
  for (size_t i = 0; i < search_result.size() - 1; i++) {
    draw_route(canvas, search_result[i], search_result[i]);
  }

  return 0;
}
