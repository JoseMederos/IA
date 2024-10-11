#include <iostream>
#include <thread>
#include <fstream>
#include "laberinto.h"


int main(int argc, char *argv[]) {
  char* filename = argv[1];

  Laberinto laberinto(filename);

  std::cout << laberinto << std::endl;
  laberinto.AStar();

  
  return 0;
}