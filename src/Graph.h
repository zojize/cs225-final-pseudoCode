#pragma once

#include <vector>

template <typename T>
class Graph {
public:
  Graph();

  /**
   * Adds a vertex to the graph
   */
  void add_vertex(T);
  /**
   * remove a vertex of the graph
   */
  void remove_vertex(T);
  /**
   * Adds an edge to the graph
   *
   * @param source
   * @param destination
   * @param weight
   */
  void add_edge(T a, T b, double weight);
  /**
   * Removes an edge of the graph
   *
   * @param source
   * @param destination
   */
  void remove_edge(T, T);
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
   * Gets outgoing adjacent vertices of a vertex
   *
   * @param source
   * @param destination
   * @return whether the graph contains this edge
   * @throws std::range_error when the vertex don't exist
   */
  std::vector<T> get_adjacent(T);

  /**
   * performs a bfs walk to the graph
   *
   * @param start_node
   * @param v
   */
  void bfs_walk(T start_node, std::vector<T> &v);

private:
  // implementation tbd
};
