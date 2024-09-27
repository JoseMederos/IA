#include <iostream>
#include <fstream>
#include "grafo.h"

int main(int arc, char* argv[]) {
  std::vector<std::vector<int>> costes_;

  std::string ficheroEntrada = argv[1];
  std::fstream input;
  input.open(ficheroEntrada);
  double lineread;
  int vertices;
  input >> vertices;
  costes_.resize(vertices, std::vector<int>(vertices, 0));
  std::cout << "N de verticces: " << vertices << std::endl;
  for (int i = 0; i < vertices; i++) {
    for (int j = i + 1; j < vertices; j++) {
      input >> lineread;
      int cost = static_cast<int>(lineread);
      if (cost > 0) {
        costes_[i][j] = cost;
        costes_[j][i] = cost;
      }
    }
  }

  for (int i = 0; i < vertices; i++) {
    for (int j = 0; j < vertices; j++) {
      std::cout << costes_[i][j] << " ";
    }
    std::cout << std::endl;
  }
  return 0;
}
