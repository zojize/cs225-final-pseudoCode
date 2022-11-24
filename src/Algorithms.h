#include "Airport.h"
#include "Graph.h"
#include "Route.h"

using airport_id = unsigned int;

namespace Algorithms {
std::vector<Route> find_shortest_path_A_star(Graph<airport_id> &g,
                                             airport_id source,
                                             airport_id destination);
std::vector<Route> find_shortest_path_dijkstra(Graph<airport_id> &g,
                                               airport_id source,
                                               airport_id destination);
}; // namespace Algorithms
