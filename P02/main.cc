#include <iostream>
#include <thread>
#include <fstream>
#include "laberinto.h"


int main(int argc, char *argv[]) {
  char* filename = argv[1];

  Laberinto laberinto(filename);

  std::cout << "¿Desea cambiar el inicio? [s][n]: " << std::endl;
  char changeStart;
  std::cin >> changeStart;
  if (changeStart == 's') {
    int x, y;
    std::cout << "Ingrese la nueva posición de inicio: " << std::endl;
    std::cin >> x >> y;
    laberinto.ChangeStart(Position(x, y));
  }
  std::cout << "¿Desea cambiar el final? [s][n]: " << std::endl;
  char changeEnd;
  std::cin >> changeEnd;
  if (changeEnd == 's') {
    int x, y;
    std::cout << "Ingrese la nueva posición de final: " << std::endl;
    std::cin >> x >> y;
    laberinto.ChangeEnd(Position(x, y));
  }

  std::cout << laberinto.AStar() << std::endl;

  
  return 0;
}