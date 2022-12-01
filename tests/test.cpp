#include <catch2/catch_test_macros.hpp>

#include "Graph.h"

#include <vector>

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
