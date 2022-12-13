#include "Airport.h"
#include "Algorithms.h"
#include "Canvas.h"
#include "DisjointSets.h"
#include "Heap.h"
#include "SvgCanvas.h"
#include "Vector2d.h"
#include "cs225/RGB_HSL.h"
#include "utils.h"

#include "getopt.h"
#include <iostream>
#include <unordered_map>

using namespace std;

// clang-format off
static string usage_prompt = \
  "Finds the shortest path between airports using either A* or Dijkstra's algorithm.\n"
  "\n"
  "USAGE:\n"
  "                        ./main [OPTIONS] SOURCE_AIRPORT DESTINATION_AIRPORT\n"
  "                        ./main prims [SOURCE_AIRPORT] [OPTIONS]\n"
  "\n"
  "POSITIONAL ARGUMENTS:\n"
  "    SOURCE_AIRPORT       Airport code of the source airport.\n"
  "    DESTINATION_AIRPORT  Airport code of the destination airport.\n"
  "\n"
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
  "                         Name for the output svg.\n"
  "    --routes [=../data/routes.csv]\n"
  "                         Dataset csv filename for routes.\n"
  "    --airports [=../data/airports.csv]\n"
  "                         Dataset csv filename for airports.\n"
  "    --map [=../data/map.png]\n"
  "                         World map image file, has to be png.\n"
  "\n"
  "SUBCOMMANDS:\n"
  "    prims [SOURCE_AIRPORT=LAX]\n"
  "                         Outputs a svg image for the result of running prims algorithm.\n"
  ;
// clang-format on

static string mode = "text";
static string algorithm = "dijkstra";
static string outfile = "output.svg";
static string routes_fname = "../data/routes.csv";
static string airports_fname = "../data/airports.csv";
static string map_fname = "../data/map.png";
static string source = "";
static string dest = "";

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

  bool prims = argc - optind >= 1 && lowercase(string(argv[optind])) == "prims";

  if (!prims && argc - optind < 2) {
    cerr << "Must provide both SOURCE_AIRPORT and DESTINATION_AIRPORT.";
    return 1;
  }

  if (prims && (argc - optind >= 2))
    source = argv[optind + 1];
  else if (prims)
    source = "lax";
  else
    source = argv[optind];
  source = lowercase(source);
  if (!prims) {
    dest = argv[optind + 1];
    dest = lowercase(dest);
  }

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
  if (!prims && m_airports.find(dest) == m_airports.end()) {
    cerr << "DESTINATION_AIRPORT " << dest << " not found." << endl;
    return 1;
  }

  Airport const& source_airport = airports[m_airports[source]];
  Airport const& dest_airport = airports[m_airports[dest]];

  Graph<Airport> g;
  cout << "Building Graph<Airport>..." << endl;
  build_graph(g, airports, routes);
  cout << "Finished building Graph<Airport>" << endl;

  if (prims) {

    cout << "Running Prim's algorithm..." << endl;
    Graph<Airport> result;
    Algorithms::prims(g, source_airport, result);
    cout << "Finished running Prim's algorithm" << endl;

    cout << "Generating svg..." << endl;
    vector<Airport> vertices;
    result.get_all_vertices(vertices);
    vector<typename Graph<Airport>::Edge> edges;
    result.get_all_edges(edges);

    cs225::PNG map;
    map.readFromFile(map_fname);

    SvgCanvas canvas(map.width(), map.height());
    canvas.image(map_fname);

    DisjointSets dset;
    dset.add_elements(airports.size());
    for (size_t i = 0; i < edges.size(); i++) {
      dset.set_union(m_airports[to_string(edges[i].source.id)],
                     m_airports[to_string(edges[i].destination.id)]);
    }
    int connected_components = dset.size_sets(true);
    cout << "comps: " << connected_components << endl;

    cs225::hslaColor hsl{0, 0.8, 0.6, 1};
    string *colors = new string[connected_components];

    double step = 360 / connected_components;
    for (int i = 0; i < connected_components; i++) {
      cs225::rgbaColor rgb = cs225::hsl2rgb(hsl);
      colors[i] = colors[i] + "rgba(" + to_string(rgb.r) + "," +
                  to_string(rgb.g) + "," + to_string(rgb.b) + ")";
      hsl.h += step;
    }

    canvas.attrs["fill"] = "#ffffff";
    canvas.attrs["stroke"] = "#000000";
    for (size_t i = 0; i < vertices.size(); i++) {
      if (dset.size(m_airports[to_string(vertices[i].id)]) < 2)
        continue;

      Airport const& a = vertices[i];
      Vector2d<double> p = lat_lon_to_offsets(a.latitude, a.longitude,
                                              canvas.width, canvas.height);
      canvas.circle(p.x, p.y, 3);
    }

    canvas.attrs["fill"] = "none";
    unordered_map<int, size_t> color_indices;
    size_t color_index = 0;
    for (size_t i = 0; i < edges.size(); i++) {
      size_t key = dset.find(m_airports[to_string(edges[i].source.id)]);
      if (color_indices.find(key) == color_indices.end())
        color_indices[key] = color_index++;
      canvas.attrs["stroke"] = colors[color_indices[key]];
      draw_route(canvas, edges[i].source, edges[i].destination);
    }

    canvas.write_to_file(outfile);

    cout << "generated svg at " << outfile << endl;

    delete[] colors;
    return 0;
  }

  cout << "Running " << algorithm << " from " << source_airport.name << " to "
       << dest_airport.name << "..." << endl;
  vector<Airport> search_result;
  search_result = algorithm == "dijkstra"
                      ? Algorithms::find_shortest_path_dijkstra(
                            g, source_airport, dest_airport)
                      : Algorithms::find_shortest_path_A_star(g, source_airport,
                                                              dest_airport);
  cout << "Finished running " << algorithm << endl;

  if (search_result.size() == 0) {
    cout << "No viable path found for " << source << " and " << dest << "."
         << endl;
    return 0;
  }

  if (mode == "text") {
    for (size_t i = 0; i < search_result.size() - 1; i++)
      cout << search_result[i].name << " ->" << endl;
    cout << search_result.back().name << endl;
    return 0;
  }

  cout << "Generating svg..." << endl;

  cs225::PNG map;
  map.readFromFile(map_fname);

  SvgCanvas canvas(map.width(), map.height());
  canvas.image(map_fname);

  canvas.attrs["fill"] = "#ffffff";
  canvas.attrs["stroke"] = "#000000";
  for (size_t i = 0; i < search_result.size(); i++) {
    Airport const& a = search_result[i];
    Vector2d<double> p = lat_lon_to_offsets(a.latitude, a.longitude,
                                            canvas.width, canvas.height);
    canvas.circle(p.x, p.y, 3);
  }

  canvas.attrs["stroke"] = "#ff0000";
  canvas.attrs["stroke-width"] = "5";
  canvas.attrs["fill"] = "none";
  for (size_t i = 0; i < search_result.size() - 1; i++) {
    draw_route(canvas, search_result[i], search_result[i + 1]);
  }
  canvas.attrs.erase("stroke-width");

  canvas.attrs["fill"] = "#ffffff";
  canvas.attrs["stroke"] = "#000000";
  canvas.attrs["font-family"] = "Arial, Helvetica, sans-serif";
  canvas.attrs["font-weight"] = "bold";
  canvas.attrs["font-size"] = "30";
  for (size_t i = 0; i < search_result.size(); i++) {
    Airport const& a = search_result[i];
    Vector2d<double> p = lat_lon_to_offsets(a.latitude, a.longitude,
                                            canvas.width, canvas.height);
    canvas.text(p.x, p.y, a.iata == "\\N" ? a.name : a.iata);
  }
  canvas.attrs.erase("font-family");
  canvas.attrs.erase("font-weight");
  canvas.attrs.erase("font-size");

  canvas.write_to_file(outfile);

  cout << "generated svg at " << outfile << endl;

  return 0;
}
