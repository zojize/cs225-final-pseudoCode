#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#include "Airport.h"
#include "Algorithms.h"
#include "CsvReader.h"
#include "Graph.h"
#include "utils.h"

using namespace std;

using Algorithms::TraversalLabel::CROSS;
using Algorithms::TraversalLabel::DISCOVERY;
using Algorithms::TraversalLabel::UNEXPLORED;
using Algorithms::TraversalLabel::VISITED;

vector<string> airport_name_10() {
  vector<string> names;
  names.push_back("Goroka Airport");
  names.push_back("Madang Airport");
  names.push_back("Mount Hagen Kagamuga Airport");
  names.push_back("Nadzab Airport");
  names.push_back("Port Moresby Jacksons International Airport");
  names.push_back("Wewak International Airport");
  names.push_back("Narsarsuaq Airport");
  names.push_back("Godthaab / Nuuk Airport");
  names.push_back("Kangerlussuaq Airport");
  names.push_back("Thule Air Base");
  return names;
}

vector<double> airport_latitude_10() {
  vector<double> latitude;
  latitude.push_back(-6.081689834590001);
  latitude.push_back(-5.20707988739);
  latitude.push_back(-5.826789855957031);
  latitude.push_back(-6.569803);
  latitude.push_back(-9.443380355834961);
  latitude.push_back(-3.58383011818);
  latitude.push_back(61.1604995728);
  latitude.push_back(64.19090271);
  latitude.push_back(67.0122218992);
  latitude.push_back(-68.7032012939);
  return latitude;
}

vector<double> airport_longitude_10() {
  vector<double> longitude;
  longitude.push_back(145.391998291);
  longitude.push_back(145.789001465);
  longitude.push_back(144.29600524902344);
  longitude.push_back(146.725977);
  longitude.push_back(147.22000122070312);
  longitude.push_back(143.669006348);
  longitude.push_back(-45.4259986877);
  longitude.push_back(-51.6781005859);
  longitude.push_back(-50.7116031647);
  longitude.push_back(-68.7032012939);
  return longitude;
}

template <typename T>
void match_vector(std::vector<T> const& result, std::vector<T> const& answer) {
  REQUIRE(result.size() == answer.size());
  for (size_t i = 0; i < answer.size(); i++)
    REQUIRE(result[i] == answer[i]);
}

void build_char_graph(Graph<char>& g, string s) {
  for (size_t i = 0; i < s.size(); i += 2) {
    while (s[i] == ',' || s[i] == ' ')
      i++;
    g.add_edge(s[i], s[i + 1], 1);
  }
}

template <typename T>
void match_labels(Algorithms::Labels<T> const& result,
                  Algorithms::Labels<T> const& answer) {
  REQUIRE(result.first.size() == answer.first.size());
  REQUIRE(result.second.size() == answer.second.size());

  for (auto p : answer.first) {
    REQUIRE(Algorithms::get_label(answer, p.first) ==
            Algorithms::get_label(result, p.first));
  }
  for (auto p : answer.second) {
    auto source = p.first;
    REQUIRE(p.second.size() == result.second.at(source).size());
    for (auto p : p.second) {
      auto destination = p.first;
      REQUIRE(get_label(answer, source, destination) ==
              get_label(result, source, destination));
    }
  }
}

template <typename T>
void check_valid_bfs(Graph<T> const& g, std::vector<T> const& bfs,
                     T const& start) {
  unordered_map<T, size_t> m_dist;
  queue<T> q;
  q.push(start);
  m_dist[start] = 0;
  while (!q.empty()) {
    T& node = q.front();
    q.pop();
    size_t d = m_dist[node];
    for (auto adj : g.get_adjacent(node)) {
      if (m_dist.find(adj) != m_dist.end())
        continue;
      m_dist[adj] = d + 1;
      q.push(adj);
    }
  }

  REQUIRE(m_dist.size() == bfs.size());
  if (bfs.size() <= 1)
    return;
  REQUIRE(m_dist.find(bfs[0]) != m_dist.end());
  // a bfs is valid if all connected nodes from start
  // are visited and are in increasing order
  for (size_t i = bfs.size() - 1; i > 0; i--) {
    REQUIRE(m_dist.find(bfs[i]) != m_dist.end());
    REQUIRE(m_dist[bfs[i]] >= m_dist[bfs[i - 1]]);
  }
}

TEST_CASE("Graph basics", "[graph]") {
  Graph<int> g;

  for (int i = 0; i < 9; i++)
    g.add_edge(i, i + 1, i * (i + 1));

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      if (j == i + 1) {
        REQUIRE(g.contains_edge(i, j));
        REQUIRE(g.get_edge_weight(i, j) == i * j);
        match_vector(g.get_adjacent(i), {j});
      } else {
        REQUIRE(!g.contains_edge(i, j));
      }
    }
  }

  for (int i = 0; i < 9; i++) {
    if (i % 2)
      g.remove_edge(i, i + 1);
  }

  for (int i = 0; i < 9; i++) {
    if (i % 2) {
      REQUIRE(!g.contains_edge(i, i + 1));
      REQUIRE_THROWS(g.get_edge_weight(i, i + 1));
    }
  }
}

TEST_CASE("BFS no node or edge", "[Graph]") {
  Graph<int> g{};
  vector<int> correct;
  vector<int> bfs = g.bfs_walk(0);
  // REQUIRE(bfs == correct);
}

TEST_CASE("BFS one node with no edge", "[Graph]") {
  Graph<int> g{};
  g.add_vertex(0);
  vector<int> correct{0};
  vector<int> bfs = g.bfs_walk(0);
  // REQUIRE(bfs == correct);
  check_valid_bfs(g, bfs, 0);
}

TEST_CASE("BFS linked list start from head", "[Graph]") {
  Graph<int> g{};
  for (int i = 0; i < 5; i++) {
    g.add_vertex(i);
  }
  g.add_edge(0, 1, 1);
  g.add_edge(1, 2, 8);
  g.add_edge(2, 3, 4);
  g.add_edge(3, 4, 2);

  vector<int> correct{0, 1, 2, 3, 4};

  vector<int> bfs = g.bfs_walk(0);
  REQUIRE(bfs == correct);
}

TEST_CASE("BFS linked list start in the mid", "[Graph]") {
  Graph<int> g{};
  for (int i = 0; i < 5; i++) {
    g.add_vertex(i);
  }
  g.add_edge(0, 1, 1);
  g.add_edge(1, 2, 8);
  g.add_edge(2, 3, 4);
  g.add_edge(3, 4, 2);

  vector<int> correct{1, 2, 3, 4};

  vector<int> bfs = g.bfs_walk(1);
  REQUIRE(bfs == correct);
}

TEST_CASE("BFS linked list start in the end", "[Graph]") {
  Graph<int> g{};
  for (int i = 0; i < 5; i++) {
    g.add_vertex(i);
  }
  g.add_edge(0, 1, 1);
  g.add_edge(1, 2, 8);
  g.add_edge(2, 3, 4);
  g.add_edge(3, 4, 2);

  vector<int> correct{4};

  vector<int> bfs = g.bfs_walk(4);
  check_valid_bfs(g, bfs, 4);
}

TEST_CASE("BFS: complex graph", "[Graph]") {
  Graph<int> g{};
  for (size_t i = 0; i < 10; i++) {
    g.add_vertex(i);
  }
  g.add_edge(1, 0, 1);
  g.add_edge(1, 3, 8);
  g.add_edge(1, 2, 2);
  g.add_edge(1, 5, 3);
  g.add_edge(1, 7, 3);

  g.add_edge(2, 3, 4);
  g.add_edge(3, 4, 2);
  g.add_edge(5, 6, 1);
  g.add_edge(6, 7, 1);
  g.add_edge(6, 9, 4);
  g.add_edge(7, 1, 5);
  g.add_edge(8, 9, 3);
  g.add_edge(9, 8, 3);

  vector<int> bfs = g.bfs_walk(1);
  check_valid_bfs(g, bfs, 1);

  vector<int> bfs5 = g.bfs_walk(5);
  check_valid_bfs(g, bfs5, 5);
}

/**
 *    A
 *   ↙ ↘
 *  B ↔ C
 *  ↓   ↓
 *  D → E
 *
 */
TEST_CASE("BFS: graph labeling simple", "[Graph][BFS]") {
  Graph<char> g;
  string graph_repr = "AB,AC,BC,CB,BD,CE,DE";
  build_char_graph(g, graph_repr);
  Algorithms::Labels<char> labels;

  Algorithms::Labels<char> answer;
  for (char c : "ABCDE")
    if (c)
      set_label(answer, c, VISITED);
  set_label(answer, 'A', 'B', DISCOVERY);
  set_label(answer, 'A', 'C', DISCOVERY);
  set_label(answer, 'B', 'C', CROSS);
  set_label(answer, 'B', 'D', DISCOVERY);
  set_label(answer, 'C', 'B', CROSS);
  set_label(answer, 'C', 'E', DISCOVERY);
  set_label(answer, 'D', 'E', CROSS);

  Algorithms::bfs_walk(g, 'A', labels);
  // std::cout << labels << endl;
  match_labels(labels, answer);
}

TEST_CASE("Graph: build graph", "[Graph][build_graph]") {
  Graph<Airport> g;

  vector<Airport> airports;
  vector<Route> routes;

  load_data(airports, "../data/airports.csv", routes, "../data/routes.csv");

  build_graph(g, airports, routes);

  std::unordered_map<unsigned int, size_t> m_airports;

  for (size_t i = 0; i < airports.size(); i++)
    m_airports[airports[i].id] = i;

  for (auto r : routes) {
    Airport const& source = airports[m_airports[r.source_airport_id]];
    Airport const& destination = airports[m_airports[r.destination_airport_id]];
    double distance = geo_distance(source, destination);
    REQUIRE(approx_eq(g.get_edge_weight(source, destination), distance));
  }
}

TEST_CASE("Algorithm: Dijkstra find shortest path", "[Algorithms]""[Dijkstra]") {
  Graph<int> g{};
  for (size_t i = 0; i < 10; i++) {
    g.add_vertex(i);
  }
  g.add_edge(1, 0, 1);
  g.add_edge(1, 3, 8);
  g.add_edge(1, 2, 2);
  g.add_edge(1, 5, 3);
  g.add_edge(1, 7, 100);

  g.add_edge(0, 9, 100);
  g.add_edge(0, 8, 1);
  g.add_edge(8, 7, 1);

  g.add_edge(2, 3, 4);
  g.add_edge(3, 4, 2);
  g.add_edge(5, 6, 6);
  g.add_edge(6, 7, 1);
  g.add_edge(6, 9, 4);
  g.add_edge(7, 1, 5);
  g.add_edge(7, 6, 1);
  g.add_edge(8, 9, 100);
  g.add_edge(9, 8, 3);

  int start = 1;
  int end = 9;
  vector<int> shortestPath = find_shortest_path_dijkstra(g, 1, 9);
  vector<int> correctPath = {9, 6, 7, 8, 0, 1};
  REQUIRE(shortestPath == correctPath);
  
  vector<int> shortestPath2 = find_shortest_path_dijkstra(g, 1, 4);
  vector<int> correctPath2 = {4, 3, 2, 1};
  REQUIRE(shortestPath2 == correctPath2);

  vector<int> shortestPath3 = find_shortest_path_dijkstra(g, 2, 4);
  vector<int> correctPath3 = {4, 3, 2};
  REQUIRE(shortestPath3 == correctPath3);

  vector<int> shortestPath4 = find_shortest_path_dijkstra(g, 0, 5);
  vector<int> correctPath4 = {5, 1, 7, 8, 0};
  REQUIRE(shortestPath4 == correctPath4);

  vector<int> shortestPath5 = find_shortest_path_dijkstra(g, 1, 1);
  vector<int> correctPath5;
  REQUIRE(shortestPath5 == correctPath5);

  vector<int> shortestPath6 = find_shortest_path_dijkstra(g, 4, 3);
  vector<int> correctPath6;
  REQUIRE(shortestPath6 == correctPath6);
}


TEST_CASE("Airport: Dijkstra find shortest path", "[Algorithms]""[Dijkstra]") {
  Graph<Airport> g;
  CsvReader reader_airports("../data/airports.csv");
  CsvReader reader_routes("../data/routes.csv");

  vector<Airport> airports;
  for (auto a : reader_airports) {
    airports.push_back(Airport{a});
  }

  vector<Route> routes;
  for (auto r : reader_routes) {
    try {
      routes.push_back(Route{r});
    } catch (std::exception const& e) {
    }
  }

  build_graph(g, airports, routes);
  vector<Airport> airport;
  g.get_all_vertices(airport);
  for (size_t i = 0; i < 1000; i++) {
    vector<Airport> shortestPathD = find_shortest_path_dijkstra(g, airport[0], airports[i]);
    vector<Airport> shortestPathA = find_shortest_path_A_star(g, airport[0], airports[i]);
    REQUIRE(shortestPathD == shortestPathA);
  }
}
