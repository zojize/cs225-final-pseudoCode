#include "Airport.h"
#include "Graph.h"
#include "Route.h"

using airport_id = unsigned int;

namespace Algorithms {
/**
 * Get the shortest path from source to destination using A*
 *
 * @param g  
 * @param source 
 * @param destination 
 * @returns vector of Route
 */
std::vector<Route> find_shortest_path_A_star(Graph<airport_id> &g,
                                             airport_id source,
                                             airport_id destination);
/**
 * Get the shortest path from source to destination using dijkstra
 *
 * @param g 
 * @param source 
 * @param destination 
 * @returns vector of Route
 */
std::vector<Route> find_shortest_path_dijkstra(Graph<airport_id> &g,
                                               airport_id source,
                                               airport_id destination);
}; // namespace Algorithms
