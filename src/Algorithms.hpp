#include <queue>
#include <stdexcept>

template <typename T>
Algorithms::TraversalLabel Algorithms::get_label(Labels<T>& labels, T vertex) {
  if (labels.first.find(vertex) != labels.first.end())
    return labels.first[vertex];
  throw std::range_error("non-existent vertex");
}

template <typename T>
Algorithms::TraversalLabel Algorithms::get_label(Labels<T>& labels, T source,
                                                 T destination) {
  if (labels.second.find(source) != labels.second.end() &&
      labels.second[source].find(destination) != labels.second[source].end())
    return labels.second[source][destination];
  throw std::range_error("non-existent edge");
}

template <typename T>
Algorithms::TraversalLabel Algorithms::get_label(Labels<T>& labels,
                                                 typename Graph<T>::Edge edge) {
  return get_label(labels, edge.source, edge.destination);
}

template <typename T>
void set_label(Algorithms::Labels<T>& labels, T vertex,
               Algorithms::TraversalLabel label) {
  labels.first[vertex] = label;
}

template <typename T>
void set_label(Algorithms::Labels<T>& labels, T source, T destination,
               Algorithms::TraversalLabel label) {
  if (labels.second.find(source) == labels.second.end())
    labels.second.insert({source, {}});
  labels.second[source].insert({destination, label});
}

template <typename T>
void set_label(Algorithms::Labels<T>& labels, typename Graph<T>::Edge edge,
               Algorithms::TraversalLabel label) {
  set_label(labels, edge.source, edge.destination, label);
}

template <typename T>
void bfs_walk(Graph<T> const& g, T const& v, Algorithms::Labels<T>& labels) {
  using Algorithms::TraversalLabel;

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
void Algorithms::bfs_walk(Graph<T> const& g, Labels<T>& labels) {
  std::cout << "bfs walking!" << std::endl;

  std::vector<T> vertices;
  g.get_all_vertices(vertices);
  std::vector<typename Graph<T>::Edge> edges;
  g.get_all_edges(edges);

  for (T& v : vertices)
    set_label(labels, v, TraversalLabel::UNEXPLORED);
  for (auto& e : edges)
    set_label(labels, e, TraversalLabel::UNEXPLORED);

  for (T& v : vertices) {
    if (get_label(labels, v) == TraversalLabel::UNEXPLORED)
      bfs_walk(g, v, labels);
  }
}
