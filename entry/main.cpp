#include "CsvReader.h"
#include <iostream>

using namespace std;

int main() {
  CsvReader r("../data/airlines.csv");
  for (auto it : r) {
    std::cout << "[";
    for (auto i : it)
      std::cout << i << ", ";
    std::cout << "]" << std::endl;
  }
}
