#include <iostream>
#include "grafo.h"

int main(int arc, char* argv[]) {
  std::string ficheroEntrada = argv[1];
  int origen, destino;
  
  std::cout << "Indique el nodo origen: ";
  std::cin >> origen;
  std::cout << "Indique el nodo destino: ";
  std::cin >> destino;
  std::cout << std::endl;
  Grafo grafo;
  int coste_total = 0;
  grafo.AddCosts(ficheroEntrada);
  grafo.Print();
  grafo.DFS_search(origen, destino, coste_total);
  return 0;
}
