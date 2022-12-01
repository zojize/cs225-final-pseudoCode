#include <catch2/catch_test_macros.hpp>

#include "Graph.h"

#include <vector>

#include "CsvReader.h"

using namespace std;
template <typename T>
void match_vector(std::vector<T> result, std::vector<T> answer) {
  REQUIRE(result.size() == answer.size());
  for (size_t i = 0; i < answer.size(); i++)
    REQUIRE(result[i] == answer[i]);
}

TEST_CASE("Graph basics", "[graph]") {
  Graph<int> g;

  for (int i = 0; i < 9; i++)
    g.add_edge(i, i + 1, i * (i + 1));

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      if (j == i + 1) {
        REQUIRE(g.contains_edge(i, j));
        REQUIRE(g.get_edge_weight(i, j) == i * j);
        match_vector(g.get_adjacent(i), {j});
      } else {
        REQUIRE(!g.contains_edge(i, j));
      }
    }
  }

  for (int i = 0; i < 9; i++) {
    if (i % 2)
      g.remove_edge(i, i + 1);
  }

  for (int i = 0; i < 9; i++) {
    if (i % 2) {
      REQUIRE(!g.contains_edge(i, i + 1));
      REQUIRE_THROWS(g.get_edge_weight(i, i + 1));
    }
  }
}

TEST_CASE("BFS no node or edge", "[Graph]") {
  Graph<int> g{};
  vector<int> correct;
  vector<int> bfs = g.bfs_walk(0);
  REQUIRE(bfs == correct);
}

TEST_CASE("BFS one node with no edge", "[Graph]") {
  Graph<int> g{};
  g.add_vertex(0);
  vector<int> correct{0};
  vector<int> bfs = g.bfs_walk(0);
  REQUIRE(bfs == correct);
}

TEST_CASE("BFS linked list start from head", "[Graph]") {
  Graph<int> g{};
  for (int i = 0; i < 5; i++) {
    g.add_vertex(i);
  }
  g.add_edge(0, 1, 1);
  g.add_edge(1, 2, 8);
  g.add_edge(2, 3, 4);
  g.add_edge(3, 4, 2);

  vector<int> correct {0, 1, 2, 3, 4};

  vector<int> bfs = g.bfs_walk(0);
  REQUIRE(bfs == correct);
}

TEST_CASE("BFS linked list start in the mid", "[Graph]") {
  Graph<int> g{};
  for (int i = 0; i < 5; i++) {
    g.add_vertex(i);
  }
  g.add_edge(0, 1, 1);
  g.add_edge(1, 2, 8);
  g.add_edge(2, 3, 4);
  g.add_edge(3, 4, 2);

  vector<int> correct {1, 2, 3, 4};

  vector<int> bfs = g.bfs_walk(1);
  REQUIRE(bfs == correct);
}

TEST_CASE("BFS linked list start in the end", "[Graph]") {
  Graph<int> g{};
  for (int i = 0; i < 5; i++) {
    g.add_vertex(i);
  }
  g.add_edge(0, 1, 1);
  g.add_edge(1, 2, 8);
  g.add_edge(2, 3, 4);
  g.add_edge(3, 4, 2);

  vector<int> correct{4};

  vector<int> bfs = g.bfs_walk(4);
  REQUIRE(bfs == correct);
}

