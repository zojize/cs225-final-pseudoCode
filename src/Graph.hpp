#include "Graph.h"
#include "utils.h"

#define _USE_MATH_DEFINES
#include <map>
#include <queue>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <cmath>

template <typename Graph>
Edge<Graph>::Edge(Vertex source, Vertex destination, double weight)
    : source(source), destination(destination), weight(weight){};

template <typename Graph>
bool Edge<Graph>::operator==(Edge<Graph> const& other) const {
  return this == &other ||
         (source == other.source && destination == other.destination &&
          weight == other.weight);
}

template <typename Graph>
std::ostream& operator<<(std::ostream& os, Edge<Graph> const& e) {
  return os << "Edge { " << e.source << " [" << e.weight << "]=> "
            << e.destination << " }";
}

template <typename Graph>
size_t std::hash<Edge<Graph>>::operator()(Edge<Graph> const& e) const {
  size_t seed = 0;
  hash_combine(seed, e.source);
  hash_combine(seed, e.destination);
  hash_combine(seed, e.weight);
  return seed;
}

template <typename T>
void Graph<T>::add_vertex(T v) {
  if (!contains_vertex(v))
    _adj_list[v] = {};
}

template <typename T>
void Graph<T>::remove_vertex(T v) {
  if (!contains_vertex(v))
    return;

  for (auto p : _adj_list[v])
    p->second.erase(v);

  _adj_list.erase(v);
}

template <typename T>
void Graph<T>::get_all_vertices(std::vector<T>& v) const {
  for (auto p : _adj_list)
    v.push_back(p.first);
}

template <typename T>
void Graph<T>::add_edge(T source, T destination, double weight) {
  add_vertex(source);
  add_vertex(destination);
  _adj_list[source][destination] = Edge(source, destination, weight);
}

template <typename T>
void Graph<T>::remove_edge(T source, T destination) {
  if (contains_edge(source, destination))
    _adj_list[source].erase(destination);
}

template <typename T>
void Graph<T>::get_all_edges(std::vector<Edge>& v) const {
  std::unordered_map<T, std::unordered_set<T>> seen;
  for (auto const& p : _adj_list) {
    for (auto const& p : p.second) {
      auto& edge = p.second;
      if (seen.find(edge.source) == seen.end() ||
          seen[edge.source].find(edge.destination) == seen[edge.source].end()) {
        v.push_back(edge);
        if (seen.find(edge.source) == seen.end())
          seen.insert({edge.source, {}});
        seen[edge.source].insert(edge.destination);
      }
    }
  }
}

template <typename T>
double Graph<T>::get_edge_weight(T source, T destination) const {
  if (contains_edge(source, destination))
    return _adj_list.at(source).at(destination).weight;
  throw std::range_error("non-existent edge");
}

template <typename T>
bool Graph<T>::contains_edge(T source, T destination) const {
  return (contains_vertex(source) &&
          _adj_list.at(source).find(destination) != _adj_list.at(source).end());
}

template <typename T>
bool Graph<T>::contains_vertex(T v) const {
  return _adj_list.find(v) != _adj_list.end();
}

template <typename T>
std::vector<T> Graph<T>::get_adjacent(T v) const {
  if (!contains_vertex(v))
    return {};

  std::vector<T> adj;
  for (auto p : _adj_list.at(v))
    adj.push_back(p.first);

  return adj;
}

/**
 * performs a bfs walk to the graph
 *
 * @param start_node
 */
template <typename T>
std::vector<T> Graph<T>::bfs_walk(T start_node) {
  using namespace std;

  vector<T> airports;
  if (!contains_vertex(start_node))
    return airports;
  queue<T> BFS_queue;
  map<T, bool> visited;
  visited[start_node] = true;
  BFS_queue.push(start_node);

  while (!BFS_queue.empty()) {
    start_node = BFS_queue.front();
    vector<T> adj = get_adjacent(start_node);
    airports.push_back(start_node);
    BFS_queue.pop();
    if (adj.empty())
      continue;
    for (T it : adj) {
      if (visited.find(it) == visited.end()) {
        visited[it] = true;
        BFS_queue.push(it);
      }
    }
  }
  return airports;
}
