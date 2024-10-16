#include <iostream>
#include <thread>
#include <fstream>
#include "laberinto.h"

int main(int argc, char *argv[]) {
  std::ofstream output("output.txt");
  std::vector<Laberinto> laberintos;
  std::string tabla = "n         m         S         E         Coste     Nodos Gen.     Nodos Ins.     \n";
    for (int i = 1; i < argc; i++) {
      char* filename = argv[i];
      Laberinto laberinto1(filename);
      Laberinto laberinto2(filename, Euclidean);
      laberintos.push_back(laberinto1);
      laberintos.push_back(laberinto2);
    }
    std::cout << "¿Desea cambiar el inicio del laberinto? [s][n]: " << std::endl;
    char changeStart;
    std::cin >> changeStart;

    int x_s, y_s;
    if (changeStart == 's') {
      std::cout << "Ingrese la nueva posición de inicio: " << std::endl;
      std::cin >> x_s >> y_s;
    }
    
    std::cout << "¿Desea cambiar el final del laberinto ? [s][n]: " << std::endl;
    char changeEnd;
    std::cin >> changeEnd;

    int x_e, y_e;
    if (changeEnd == 's') {
      std::cout << "Ingrese la nueva posición de final: " << std::endl;
      std::cin >> x_e >> y_e;
    }

    for (size_t i = 0; i < laberintos.size(); i++) {
      if (changeStart == 's') {
        laberintos[i].ChangeStart(Position(x_s, y_s));
      }
      if (changeEnd == 's') {
        laberintos[i].ChangeEnd(Position(x_e, y_e));
      }
      output << "LABERINTO " << i + 1 << std::endl;
      output << laberintos[i].AStar(tabla) << std::endl;
      output << "____________________________________________________________________________________" << std::endl;
    }
  
  return 0;
}