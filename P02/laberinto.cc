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

// function to search priority queue
bool findInPriorityQueue(std::priority_queue<Nodo>& pq, Nodo node) {
  while (!pq.empty()) {
    Nodo current = pq.top();
    pq.pop();
    if (current.pos == node.pos) {
      return true;
    }
  }
  return false;
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
// INDEX (ROW, COLUMN)
// M_1: START = (4, 0), END = (5, 9)
void Laberinto::AStar() {
  Nodo startNode = {start_, 0, Manhattan(start_.first, start_.second, end_.first, end_.second), nullptr};
  std::priority_queue<Nodo> openSet;
  std::set<Nodo> closedSet;
  openSet.push(startNode);

  while (!openSet.empty()) {
    // Selecciona el nodo de menor cose f(n)
    Nodo current = openSet.top();
    openSet.pop();

    if (current.pos == end_) {
      std::cout << "Camino encontrado" << std::endl;
      Nodo* currentAux = &current;
      while (currentAux != nullptr) {
        map_[currentAux->pos.first][currentAux->pos.second] = 2;
        currentAux = currentAux->parent;
      }
      Print();
      return;
    }

    // Se inserta en los nodos cerrados
    closedSet.insert(current);

    std::vector<Position> neighbors = {
      {current.pos.first + 0, current.pos.second + 1}, {current.pos.first + 1, current.pos.second + 1}, 
      {current.pos.first + 1, current.pos.second + 0}, {current.pos.first + 1, current.pos.second - 1},
      {current.pos.first + 0, current.pos.second - 1}, {current.pos.first - 1, current.pos.second - 1},
      {current.pos.first - 1, current.pos.second + 0}, {current.pos.first - 1, current.pos.second + 1}
    };

    for (size_t i = 0; i < neighbors.size(); i++) {
      Nodo aux = {neighbors[i]};
      
      if (aux.pos.first < 0 || aux.pos.first >= rows_ || aux.pos.second < 0 || aux.pos.second >= columns_) {
        continue;
      }

      if(map_[aux.pos.first][aux.pos.second] != 0) {
        continue;
      }
      
      // Si el nodo no esta ni en A, ni en C
      if (!findInPriorityQueue(openSet, aux) && !closedSet.count(aux)) {
        // si indice es divisible por 2 el movimiento es vertical o horizontal, gracias al vector neighbors
        if (i % 2 == 0) {
          aux.gCost = current.gCost + 5;
        } else {
          aux.gCost = current.gCost + 7;
        }
        aux.hCost = Manhattan(aux.pos.first, aux.pos.second, end_.first, end_.second);
        aux.parent = &current;
        openSet.push(aux);
      } else if (findInPriorityQueue(openSet, aux)) {
        // Si el nodo esta en A
        Nodo current = openSet.top();
        if (aux.gCost < current.gCost) {
          current.gCost = aux.gCost;
          current.parent = aux.parent;
        }
      }

    }
  }
  std::cout << "No existe camino" << std::endl;

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

