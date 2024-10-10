#include <iostream>
#include <fstream>
#include <queue>
#include <set>
#include "laberinto.h"

struct Nodo {
  Position pos;
  int gCost; // Costo desde el inicio hasta este nodo
  int hCost; // Costo estimado desde este nodo hasta el objetivo
  Nodo* parent;
  int fCost() const { return gCost + hCost; }
  bool operator<(const Nodo& other) const { return fCost() > other.fCost(); }
};

int Manhattan(int x1, int y1, int x2, int y2) {
  return abs(x1 - x2) + abs(y1 - y2);
}

Laberinto::Laberinto(const char* filename) {
  std::ifstream inputFile;
  inputFile.open(filename);
  int M, N;
  inputFile >> M >> N;
  rows_ = M;
  columns_ = N;
  int character;
  map_.resize(rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < columns_; j++) {
      inputFile >> character;
      map_[i].push_back(character);
      if (character == 3) {
        start_ = Position(i, j);
      } else if (character == 4) {
        end_ = Position(i, j);
      }
    }
  }  
}

void Laberinto::AStar() {
  Nodo startNode = {start_, 0, Manhattan(start_.first, start_.second, end_.first, end_.second)};
  std::priority_queue<Nodo> openSet;
  std::set<Nodo> closedSet;
  openSet.push(startNode);

  while (!openSet.empty()) {
    Nodo current = openSet.top();
    openSet.pop();
    closedSet.insert(current);

    std::vector<Position> neighbors = {
      {0, 1}, {1, 0}, {0, -1}, {-1, 0},
      {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
    };

    for (size_t i = 0; i < neighbors.size(); i++) {
      Nodo aux = {neighbors[i]};
      
      if (aux.pos.first < 0 || aux.pos.first >= rows_ || aux.pos.second < 0 || aux.pos.second >= columns_) {
        continue;
      }

      if(map_[aux.pos.first][aux.pos.second] == 0 || closedSet.count(aux)) {
        continue;
      }
    }
  }

}

std::string Laberinto::Print() const {
  std::string output = "";
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < columns_; j++) {
      std::cout << map_[i][j] << " ";
    }
    std::cout << std::endl;
  } 
  return output;
}

std::ostream& operator<<(std::ostream& os, const Laberinto& laberinto) {
  os << laberinto.Print();
  os << std::endl;
  return os;
}

