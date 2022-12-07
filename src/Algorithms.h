#include "Airport.h"
#include "Graph.h"
#include "Route.h"

#include <iostream>
#include <unordered_map>
#include <utility>

namespace Algorithms {

enum TraversalLabel {
  UNEXPLORED,
  VISITED,
  DISCOVERY,
  CROSS,
  BACK,
};

template <typename T>
using Labels =
    std::pair<std::unordered_map<T, TraversalLabel>,
              std::unordered_map<T, std::unordered_map<T, TraversalLabel>>>;

std::ostream& operator<<(std::ostream& os, TraversalLabel const& labels);

template <typename T>
std::ostream& operator<<(std::ostream& os, Algorithms::Labels<T> const& labels);

template <typename T>
TraversalLabel get_label(Labels<T> const& labels, T vertex);
template <typename T>
TraversalLabel get_label(Labels<T> const& labels, T source, T destination);
template <typename T>
TraversalLabel get_label(Labels<T> const& labels, typename Graph<T>::Edge edge);

template <typename T>
void set_label(Algorithms::Labels<T>& labels, T vertex,
               Algorithms::TraversalLabel label);
template <typename T>
void set_label(Algorithms::Labels<T>& labels, T source, T destination,
               Algorithms::TraversalLabel label);
template <typename T>
void set_label(Algorithms::Labels<T>& labels, typename Graph<T>::Edge edge,
               Algorithms::TraversalLabel label);

template <typename T>
void bfs_walk(Graph<T> const& g, Labels<T>&);

/**
 * Get the shortest path from source to destination using A*
 *
 * @param g
 * @param source
 * @param destination
 * @returns vector of Route
 */
std::vector<Route> find_shortest_path_A_star(Graph<Airport>& g, Airport source,
                                             Airport destination);

/**
 * Get the shortest path from source to destination using dijkstra
 *
 * @param g
 * @param source
 * @param destination
 * @returns vector of Route
 */
std::vector<Route> find_shortest_path_dijkstra(Graph<Airport>& g,
                                               Airport source,
                                               Airport destination);
}; // namespace Algorithms

#include <Algorithms.hpp>
