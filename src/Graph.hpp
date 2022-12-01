#include "Graph.h"
#include <stdexcept>

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
void Graph<T>::add_edge(T source, T destination, double weight) {
  add_vertex(source);
  // _adj_list[source][destination] = Edge(source, destination, weight);
  _adj_list[source].insert({destination, {source, destination, weight}});
}

template <typename T>
void Graph<T>::remove_edge(T source, T destination) {
  if (contains_edge(source, destination))
    _adj_list[source].erase(destination);
}

template <typename T>
double Graph<T>::get_edge_weight(T source, T destination) {
  if (contains_edge(source, destination))
    return _adj_list[source][destination].weight;
  throw std::range_error("non-existent edge");
}

template <typename T>
bool Graph<T>::contains_edge(T source, T destination) {
  return (contains_vertex(source) &&
          _adj_list[source].find(destination) != _adj_list[source].end());
}

template <typename T>
bool Graph<T>::contains_vertex(T v) {
  return _adj_list.find(v) != _adj_list.end();
}

template <typename T>
std::vector<T> Graph<T>::get_adjacent(T v) {
  if (!contains_vertex(v))
    return {};

  std::vector<T> adj;
  for (auto p : _adj_list[v])
    adj.push_back(p.first);

  return adj;
}

template <typename T>
void Graph<T>::bfs_walk(T start_node, std::vector<T>& v) {}
