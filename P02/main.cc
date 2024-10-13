#include <iostream>
#include <thread>
#include <fstream>
#include "laberinto.h"
// DUDAS
// Implementacion?
// Complejidad de la heuristica alterna?
// El codigo tiene que hacer la busqueda con los 3 grafos y mostrar la tabla completa? Con las dos heuristicas? O es solo en la memeoria?

int main(int argc, char *argv[]) {
  std::ofstream output("output.txt");
  std::vector<Laberinto> laberintos;
    for (int i = 1; i < argc; i++) {
      char* filename = argv[i];
      Laberinto laberinto(filename);
      laberintos.push_back(laberinto);
    }
    for (size_t i = 0; i < laberintos.size(); i++) {
      std::cout << "¿Desea cambiar el inicio del laberinto " << i + 1 << "? [s][n]: " << std::endl;
      char changeStart;
      std::cin >> changeStart;
      if (changeStart == 's') {
        int x, y;
        std::cout << "Ingrese la nueva posición de inicio: " << std::endl;
        std::cin >> x >> y;
        laberintos[i].ChangeStart(Position(x, y));
      }
      std::cout << "¿Desea cambiar el final del laberinto " << i + 1 << "? [s][n]: " << std::endl;
      char changeEnd;
      std::cin >> changeEnd;
      if (changeEnd == 's') {
        int x, y;
        std::cout << "Ingrese la nueva posición de final: " << std::endl;
        std::cin >> x >> y;
        laberintos[i].ChangeEnd(Position(x, y));
      }
      output << "LABERINTO " << i + 1 << std::endl;
      output << laberintos[i].AStar() << std::endl;
      output << "____________________________________________________________________________________" << std::endl;
    }
  
  return 0;
}