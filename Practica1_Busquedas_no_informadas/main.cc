#include <iostream>
#include "grafo.h"

int main(int arc, char* argv[]) {
  std::string ficheroEntrada = argv[1];
  int origen, destino, tipo;
  std::cout << "[1] BFS\n[2] DFS\nTipo de busqueda: ";
  std::cin >> tipo;
  std::cout << "Indique el nodo origen: ";
  std::cin >> origen;
  std::cout << "Indique el nodo destino: ";
  std::cin >> destino;
  std::cout << std::endl;
  Grafo grafo;
  int coste_total = 0;
  grafo.AddCosts(ficheroEntrada);
  grafo.Print();
  if (tipo == 1) {
    grafo.BFS_search(origen, destino, coste_total);
  } else {
    grafo.DFS_search(origen, destino, coste_total);
  }
  return 0;
}
