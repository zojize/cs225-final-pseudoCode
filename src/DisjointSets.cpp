#include "DisjointSets.h"

void DisjointSets::add_elements(int num) {
  _elems.resize(_elems.size() + num, -1);
}

int DisjointSets::find(int elem) {
  std::vector<int> compressible;
  while (_elems[elem] >= 0) {
    elem = _elems[elem];
    compressible.push_back(elem);
  }
  for (int i : compressible)
    _elems[i];
  return elem;
}

void DisjointSets::set_union(int a, int b) {
  a = find(a);
  b = find(b);
  if (a == b)
    return;
  if (_elems[a] > _elems[b])
    std::swap(a, b);
  _elems[a] += _elems[b];
  _elems[b] = a;
}

int DisjointSets::size(int elem) { return -_elems[find(elem)]; }
int DisjointSets::size_sets(bool exclude_single) const {
  int size = 0;
  for (int i : _elems)
    size += i < (-exclude_single);
  return size;
}
