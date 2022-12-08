#pragma once

#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>

template <typename Graph>
struct Edge {
  using Vertex = typename Graph::Vertex;

  Edge() = default;
  Edge(Vertex source, Vertex destination, double weight);

  Vertex source;
  Vertex destination;
  double weight;

  bool operator==(Edge<Graph> const& other) const;
};

template <typename Graph>
std::ostream& operator<<(std::ostream& os, Edge<Graph> const&);

template <typename Graph>
struct std::hash<Edge<Graph>> {
  size_t operator()(Edge<Graph> const&) const;
};

template <typename T>
class Graph {
public:
  using Vertex = T;
  using Edge = Edge<Graph>;

  Graph() = default;

  /**
   * Adds a vertex to the graph
   */
  void add_vertex(T const& v);

  /**
   * remove a vertex of the graph
   */
  void remove_vertex(T const& v);

  /**
   * get all vertices
   */
  void get_all_vertices(std::vector<T>&) const;

  /**
   * Adds an edge to the graph
   *
   * @param source
   * @param destination
   * @param weight
   */
  void add_edge(T const& source, T const& destination, double weight);

  /**
   * Removes an edge of the graph
   *
   * @param source
   * @param destination
   */
  void remove_edge(T const& source, T const& destination);

  /**
   * get all edges
   */
  void get_all_edges(std::vector<Edge>&) const;

  /**
   * Gets the weight between two vertices
   *
   * @param source
   * @param destination
   * @return double
   * @throws std::range_error when vertices don't exist
   */
  double get_edge_weight(T const& source, T const& destination) const;

  /**
   * returns true if the edge exists, false otherwise
   *
   * @param source
   * @param destination
   * @return whether the graph contains this edge
   */
  bool contains_edge(T const& source, T const& destination) const;

  /**
   * returns true if the vertex exists, false otherwise
   *
   * @param v
   * @return whether the graph contains this edge
   */
  bool contains_vertex(T const& v) const;

  /**
   * Gets outgoing adjacent vertices of a vertex
   *
   * @param source
   * @param destination
   * @return whether the graph contains this edge
   * @throws std::range_error when the vertex don't exist
   */
  std::vector<T> get_adjacent(T const& v) const;

  /**
   * performs a bfs walk to the graph
   *
   * @param start_node
   * @return bfs walk result
   */
  std::vector<T> bfs_walk(T start_node);

private:
  std::unordered_map<T, std::unordered_map<T, Edge>> _adj_list;
};

#include "Graph.hpp"
