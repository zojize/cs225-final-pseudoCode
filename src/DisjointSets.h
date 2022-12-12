/* Your code here! */
#pragma once

#include <vector>

class DisjointSets {
public:
  DisjointSets() = default;

  void add_elements(int num);
  int find(int elem);
  void set_union(int a, int b);
  int size(int elem);
  int size_sets(bool exclude_single = false) const;

private:
  std::vector<int> _elems;
};
