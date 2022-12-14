// #include "Heap.h"

#include <limits>
#include <queue>
#include <stdexcept>
#include <unordered_set>

using namespace Algorithms;
using namespace std;

template <typename T>
Algorithms::TraversalLabel Algorithms::get_label(Labels<T> const& labels,
                                                 T vertex) {
  if (labels.first.find(vertex) != labels.first.end())
    return labels.first.at(vertex);
  throw std::range_error("non-existent vertex");
}

template <typename T>
Algorithms::TraversalLabel Algorithms::get_label(Labels<T> const& labels,
                                                 T source, T destination) {
  if (labels.second.find(source) != labels.second.end() &&
      labels.second.at(source).find(destination) !=
          labels.second.at(source).end())
    return labels.second.at(source).at(destination);
  throw std::range_error("non-existent edge");
}

template <typename T>
Algorithms::TraversalLabel Algorithms::get_label(Labels<T> const& labels,
                                                 typename Graph<T>::Edge edge) {
  return get_label(labels, edge.source, edge.destination);
}

template <typename T>
void Algorithms::set_label(Algorithms::Labels<T>& labels, T vertex,
                           Algorithms::TraversalLabel label) {
  labels.first[vertex] = label;
}

template <typename T>
void Algorithms::set_label(Algorithms::Labels<T>& labels, T source,
                           T destination, Algorithms::TraversalLabel label) {
  if (labels.second.find(source) == labels.second.end())
    labels.second.insert({source, {}});
  labels.second[source][destination] = label;
}

template <typename T>
void Algorithms::set_label(Algorithms::Labels<T>& labels,
                           typename Graph<T>::Edge edge,
                           Algorithms::TraversalLabel label) {
  set_label(labels, edge.source, edge.destination, label);
}

std::ostream& Algorithms::operator<<(std::ostream& os,
                                     TraversalLabel const& label) {
  switch (label) {
  case TraversalLabel::UNEXPLORED:
    return os << "UNEXPLORED";
  case TraversalLabel::VISITED:
    return os << "VISITED";
  case TraversalLabel::DISCOVERY:
    return os << "DISCOVERY";
  case TraversalLabel::CROSS:
    return os << "CROSS";
  case TraversalLabel::BACK:
    return os << "BACK";
  default:
    return os << "UNKNOWN";
  }
}

template <typename T>
std::ostream& Algorithms::operator<<(std::ostream& os,
                                     Algorithms::Labels<T> const& labels) {
  os << "{" << std::endl;
  for (auto p : labels.first) {
    os << "  " << p.first << ": " << p.second << "," << std::endl;
  }
  for (auto p : labels.second) {
    auto left = p.first;
    for (auto p : p.second) {
      os << "  " << left << "->" << p.first << ": " << p.second << ","
         << std::endl;
    }
  }
  return os << "}" << std::endl;
}

template <typename T>
void bfs_init(Graph<T> const& g, Labels<T>& labels, std::vector<T>& vertices,
              std::vector<typename Graph<T>::Edge> edges) {
  g.get_all_vertices(vertices);
  g.get_all_edges(edges);
  for (T& v : vertices) {
    set_label(labels, v, TraversalLabel::UNEXPLORED);
  }
  for (auto& e : edges) {
    set_label(labels, e, TraversalLabel::UNEXPLORED);
  }
}

template <typename T>
void bfs_walk_impl(Graph<T> const& g, T const& v, Labels<T>& labels) {
  std::queue<T> q;
  set_label(labels, v, TraversalLabel::VISITED);
  q.push(v);

  while (!q.empty()) {
    T v = q.front();
    q.pop();
    for (T w : g.get_adjacent(v)) {
      if (get_label(labels, w) == TraversalLabel::UNEXPLORED) {
        set_label(labels, v, w, TraversalLabel::DISCOVERY);
        set_label(labels, w, TraversalLabel::VISITED);
        q.push(w);
      } else if (get_label(labels, v, w) == TraversalLabel::UNEXPLORED) {
        set_label(labels, v, w, TraversalLabel::CROSS);
      }
    }
  }
}

template <typename T>
void Algorithms::bfs_walk(Graph<T> const& g, T const& v, Labels<T>& labels) {

  std::vector<T> vertices;
  std::vector<typename Graph<T>::Edge> edges;

  bfs_init(g, labels, vertices, edges);

  bfs_walk_impl(g, v, labels);
}

template <typename T>
void Algorithms::bfs_walk(Graph<T> const& g, Labels<T>& labels) {
  std::vector<T> vertices;
  std::vector<typename Graph<T>::Edge> edges;

  bfs_init(g, labels, vertices, edges);

  for (T& v : vertices) {
    if (get_label(labels, v) == TraversalLabel::UNEXPLORED)
      bfs_walk_impl(g, v, labels);
  }
}

template <typename T>
std::vector<T> Algorithms::find_shortest_path_dijkstra(Graph<T> const& g,
                                                       T source,
                                                       T destination) {
  vector<T> shortestPath;

  unordered_map<T, T>
      previousVertex; // key: current airport  value: previous airport
  unordered_map<T, double>
      weightMap; // key: airport
                 // value: cumulative weight to current airport
  unordered_map<T, bool>
      expandedVertices; // key: airport
                        // value: whether this airport is expanded
  priority_queue<Node<T>, vector<Node<T>>, greater<Node<T>>>
      minHeap; // T must be a comparable type

  vector<T> vertices;
  g.get_all_vertices(vertices);

  // initialization
  for (size_t i = 0; i < vertices.size(); i++) {
    T currAirport = vertices[i];
    expandedVertices[currAirport] = false;
    weightMap[currAirport] = numeric_limits<double>::max();
  }
  minHeap.push(Node(source, 0.0));
  weightMap[source] = 0.0;

  // traverse
  while (!minHeap.empty()) {

    // get current node from the priority queue
    T currAirport = minHeap.top().vertex;
    minHeap.pop();

    // node is visited
    if (expandedVertices[currAirport])
      continue;

    // find destination
    if (currAirport == destination)
      break;

    // update neighbors' weight if necessary
    vector<T> currAdjacent = g.get_adjacent(currAirport);
    for (T adj : currAdjacent) {
      if (!expandedVertices[adj]) {
        double currentCumulativeWight =
            weightMap[currAirport] + g.get_edge_weight(currAirport, adj);
        if (currentCumulativeWight < weightMap[adj]) {

          weightMap[adj] = currentCumulativeWight;
          previousVertex[adj] = currAirport;
        }
        minHeap.push(Node(adj, currentCumulativeWight));
        if (adj == destination)
          break;
      }
    }
    expandedVertices[currAirport] = true;
    // cout << endl;
  }

  // destination not found
  if (previousVertex.find(destination) == previousVertex.end()) {
    return shortestPath;
  } else {
    // extract path from previous
    T curr = destination;
    shortestPath.insert(shortestPath.begin(), destination);
    while (curr != source) {
      shortestPath.insert(shortestPath.begin(), previousVertex[curr]);
      curr = (previousVertex[curr]);
      if (curr == source)
        break;
    }
  }
  return shortestPath;
}

template <typename T>
std::vector<T> Algorithms::find_shortest_path_A_star(Graph<T> const& g,
                                                     T source, T destination) {
  vector<T> shortestPath;

  unordered_map<T, T>
      previousVertex; // key: current airport  value: previous airport
  unordered_map<T, double>
      weightMap; // key: airport
                 // value: cumulative weight to current airport
  unordered_map<T, bool>
      expandedVertices; // key: airport
                        // value: whether this airport is expanded
  priority_queue<Node<T>, vector<Node<T>>, greater<Node<T>>>
      minHeap; // T must be a comparable type

  vector<T> vertices;
  g.get_all_vertices(vertices);

  // initialization
  for (size_t i = 0; i < vertices.size(); i++) {
    T currAirport = vertices[i];
    expandedVertices[currAirport] = false;
    weightMap[currAirport] = numeric_limits<double>::max();
  }
  minHeap.push(Node(source, 0.0));
  weightMap[source] = 0.0;

  // traverse
  while (!minHeap.empty()) {

    // get current node from the priority queue
    T currAirport = minHeap.top().vertex;
    minHeap.pop();

    // node is visited
    if (expandedVertices[currAirport])
      continue;

    // find destination
    if (currAirport == destination)
      break;

    // update neighbors' weight if necessary
    vector<T> currAdjacent = g.get_adjacent(currAirport);
    for (T adj : currAdjacent) {
      if (!expandedVertices[adj]) {
        double currentCumulativeWight =
            weightMap[currAirport] + g.get_edge_weight(currAirport, adj);
        double difference =
            abs(currAirport - adj); // overwrite Airport operator- to do this
        double weightSum = currentCumulativeWight + difference;
        if (currentCumulativeWight < weightMap[adj]) {
          weightMap[adj] = currentCumulativeWight;
          previousVertex[adj] = currAirport;
        }
        minHeap.push(Node(adj, currentCumulativeWight));
      }
    }
    expandedVertices[currAirport] = true;
  }

  // destination not found
  if (previousVertex.find(destination) == previousVertex.end()) {
    return shortestPath;
  } else {
    // extract path from previous
    T curr = destination;
    shortestPath.insert(shortestPath.begin(), destination);
    while (curr != source) {
      shortestPath.insert(shortestPath.begin(), previousVertex[curr]);
      curr = (previousVertex[curr]);
      if (curr == source)
        break;
    }
  }
  return shortestPath;
}

template <typename T>
void Algorithms::prims(Graph<T> const& g, T const& start, Graph<T>& out) {
  unordered_map<T, T> p;
  unordered_map<T, double> d;

  vector<T> vertices;
  g.get_all_vertices(vertices);
  for (T const& v : vertices) {
    d[v] = numeric_limits<double>::max();
  }
  d[start] = 0;

  struct lt {
    unordered_map<T, double> const& d;
    lt(unordered_map<T, double> const& d) : d(d) {}
    bool operator()(T const& l, T const& r) const { return d.at(l) > d.at(r); };
  };
  priority_queue min_heap(vertices.begin(), vertices.end(), lt(d));
  // Heap<T, lt> mh(vertices, lt(d));

  double weight;
  for (size_t i = 0; i < vertices.size(); i++) {
    if (min_heap.empty())
      break;
    T m = min_heap.top();
    min_heap.pop();

    out.add_vertex(m);
    for (T const& v : g.get_adjacent(m)) {
      if (out.contains_vertex(v))
        continue;
      if ((weight = g.get_edge_weight(m, v)) < d[v]) {
        d[v] = weight;
        // https://stackoverflow.com/a/5811888/14835397
        std::make_heap(const_cast<T *>(&min_heap.top()),
                       const_cast<T *>(&min_heap.top()) + min_heap.size(),
                       lt(d));
        p[v] = m;
      }
    }
  }

  for (auto t : p)
    out.add_edge(t.second, t.first, d[t.first]);
}
