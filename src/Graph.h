#pragma once

#include <unordered_map>
#include <vector>
using namespace std;
template <typename T>
class Graph {
public:
  Graph();

  struct Edge {
    Edge() = default;
    Edge(T source, T destination, double weight)
        : source(source), destination(destination), weight(weight){};

    T source;
    T destination;
    double weight;
  };

  /**
   * Adds a vertex to the graph
   */
  void add_vertex(T v);

  /**
   * remove a vertex of the graph
   */
  void remove_vertex(T v);

  /**
   * Adds an edge to the graph
   *
   * @param source
   * @param destination
   * @param weight
   */
  void add_edge(T source, T destination, double weight);

  /**
   * Removes an edge of the graph
   *
   * @param source
   * @param destination
   */
  void remove_edge(T source, T destination);

  /**
   * Gets the weight between two vertices
   *
   * @param source
   * @param destination
   * @return double
   * @throws std::range_error when vertices don't exist
   */
  double get_edge_weight(T source, T destination);

  /**
   * returns true if the edge exists, false otherwise
   *
   * @param source
   * @param destination
   * @return whether the graph contains this edge
   */
  bool contains_edge(T source, T destination);

  /**
   * returns true if the vertex exists, false otherwise
   *
   * @param v
   * @return whether the graph contains this edge
   */
  bool contains_vertex(T v);

  /**
   * Gets outgoing adjacent vertices of a vertex
   *
   * @param source
   * @param destination
   * @return whether the graph contains this edge
   * @throws std::range_error when the vertex don't exist
   */
  std::vector<T> get_adjacent(T v);

  /**
   * performs a bfs walk to the graph
   *
   * @param start_node
   */
  std::vector<T> bfs_walk(T start_node);

  /**
   * test for bfs using simpler input
   *
   * @param start_node
   */
  std::vector<T> bfs_walk_test(T start_node);

private:
  std::unordered_map<T, std::unordered_map<T, Edge>> _adj_list;

  Edge new_(T& source, T& destination, double weight) {
    if (_adj_list.find(source) != _adj_list.end() &&
        _adj_list[source].find(destination) != _adj_list[source].end())
      return _adj_list[source][destination];
    return Edge{source, destination, weight};
  };
};

#include "Graph.hpp"
