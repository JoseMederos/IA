#include <iostream>
#include <fstream>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <iomanip>
#include <math.h>
#include "laberinto.h"

struct Nodo {
  Position pos;
  int gCost; // Costo desde el inicio hasta este nodo
  int hCost; // Costo estimado desde este nodo hasta el objetivo
  int fCost() const { return gCost + hCost; }
  bool operator<(const Nodo& other) const { return fCost() > other.fCost(); }
  bool operator==(const Nodo& other) const { return pos == other.pos; }
};

int Manhattan(int x1, int y1, int x2, int y2) {
  return (abs(x2 - x1) + abs(y2 - y1)) * 3;
}

int Euclidean(int x1, int y1, int x2, int y2) {
  return static_cast<int>(sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2)) * 3);
}

bool findInPriorityQueue(std::priority_queue<Nodo> pq, Nodo node) {
  while (!pq.empty()) {
    Nodo current = pq.top();
    pq.pop();
    if (current.pos == node.pos) {
      return true;
    }
  }
  return false;
}

Laberinto::Laberinto(const char* filename, HFunction hfunc) : hFunction_(hfunc) {
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

void Laberinto::ChangeStart(Position start) {
  map_[start_.first][start_.second] = 1;
  map_[start.first][start.second] = 3;
  start_ = start;
}

void Laberinto::ChangeEnd(Position end) {
  map_[end_.first][end_.second] = 1;
  map_[end.first][end.second] = 4;
  end_ = end;
}

// INDEX (ROW, COLUMN)
// M_1: START = (4, 0), END = (5, 9)
std::string Laberinto::AStar(std::string &tabla) {
  Nodo startNode = {start_, 0, hFunction_(start_.first, start_.second, end_.first, end_.second)};
  std::string output = "";
  std::priority_queue<Nodo> openSet;
  std::set<Position> closedSet;
  std::map<Position, Position> parentMap;
  std::vector<Position> nodosGen, nodosIns;
  openSet.push(startNode);
  nodosGen.push_back(startNode.pos);

  int interation = 0;

    Nodo current;
  while (!openSet.empty()) {
    interation++;
    if (interation == 1) {
      output += "\nIteracion: " + std::to_string(interation) + " Nodo actual: " + "\n";
    } else {
      output += "\nIteracion: " + std::to_string(interation) + " Nodo actual: " + std::to_string(current.pos.first) + "," + std::to_string(current.pos.second) + "\n";
    }

    output += "Nodos Generados:\n";
    for (size_t i = 0; i < nodosGen.size(); i++) {
      output += "(" + std::to_string(nodosGen[i].first) + "," + std::to_string(nodosGen[i].second) + ") ";
    }
    output += "\nNodos Inspeccionados:\n";
    for (size_t i = 0; i < nodosIns.size(); i++) {
      output += "(" + std::to_string(nodosIns[i].first) + "," + std::to_string(nodosIns[i].second) + ") ";
    }
    output += "\n";
    output += "_________________________________________________________________________________________________________";
    
    // Selecciona el nodo de menor cose f(n)
    current = openSet.top();
    openSet.pop();



    if (current.pos == end_) {
      nodosIns.push_back(current.pos);
      interation++;
      output += "\nIteracion: " + std::to_string(interation) + " Nodo actual: " + std::to_string(current.pos.first) + "," + std::to_string(current.pos.second) + "\n";

      output += "Nodos Generados:\n";
      for (size_t i = 0; i < nodosGen.size(); i++) {
        output += "(" + std::to_string(nodosGen[i].first) + "," + std::to_string(nodosGen[i].second) + ") ";
      }
      output += "\nNodos Inspeccionados:\n";
      for (size_t i = 0; i < nodosIns.size(); i++) {
        output += "(" + std::to_string(nodosIns[i].first) + "," + std::to_string(nodosIns[i].second) + ") ";
      }
      output += "\n";
      output += "_________________________________________________________________________________________________________";
      output += "\nCamino encontrado\n\n";
      
      std::vector<Position> path;
      std::set<Position> pathSet;
      while (current.pos != start_) {
        path.push_back(current.pos);
        pathSet.insert(current.pos);
        current.pos = parentMap[current.pos];
      }
      path.push_back(start_);
      solucion_ += Print(pathSet);
      output += "Camino: ";
      for (int i = path.size() - 1; i >= 0; i--) {
        output += "(" + std::to_string(path[i].first) + "," + std::to_string(path[i].second) + ")";
        if (i != 0) {
          output += " -> ";
        }
      }
      output += "\n";

      output += "Coste del camino: " + std::to_string(current.gCost) + "\n";
      output = solucion_ + output;

      output += "\n";
      std::stringstream tabla_edit;

      tabla_edit << std::left << std::setw(10) << rows_ 
            << std::setw(10) << columns_ 
            << std::setw(10) << "(" + std::to_string(start_.first) + "," + std::to_string(start_.second) + ")" 
            << std::setw(10) << "(" + std::to_string(end_.first) + "," + std::to_string(end_.second) + ")" 
            << std::setw(10) << current.gCost 
            << std::setw(15) << nodosGen.size() 
            << std::setw(15) << nodosIns.size() << "\n";
      tabla += tabla_edit.str();

      output += tabla;
      return output;
    }

    // Se inserta en los nodos cerrados
    closedSet.insert(current.pos);
    nodosIns.push_back(current.pos);

    std::vector<Position> neighbors = {
      {current.pos.first + 0, current.pos.second + 1}, {current.pos.first + 1, current.pos.second + 1}, 
      {current.pos.first + 1, current.pos.second + 0}, {current.pos.first + 1, current.pos.second - 1},
      {current.pos.first + 0, current.pos.second - 1}, {current.pos.first - 1, current.pos.second - 1},
      {current.pos.first - 1, current.pos.second + 0}, {current.pos.first - 1, current.pos.second + 1}
    };

    for (size_t i = 0; i < neighbors.size(); i++) {
      Nodo front = {neighbors[i]};
      if (front.pos.first < 0 || front.pos.first >= rows_ || front.pos.second < 0 || front.pos.second >= columns_) {
        continue;
      }
      // Revisa si el camino es transitable
      if(map_[front.pos.first][front.pos.second] == 1) {
        continue;
      }
      // Si ya hay un nodo en closed set con el mismo indice continue
      if (closedSet.count(front.pos)) {
        continue;
      }
      // Si el nodo no esta ni en A, ni en C
      if (!findInPriorityQueue(openSet, front) && !closedSet.count(front.pos)) {
        // si indice es divisible por 2 el movimiento es vertical o horizontal, gracias al vector neighbors
        if (i % 2 == 0) {
          front.gCost = current.gCost + 5;
        } else {
          front.gCost = current.gCost + 7;
        }
        
        front.hCost = hFunction_(front.pos.first, front.pos.second, end_.first, end_.second);
        parentMap[front.pos] = current.pos;

        //std::cout << "Nodo insertado: " << front.pos.first << "," << front.pos.second << " gCost: " << front.gCost << " hCost: " << front.hCost << " fCost: " << front.fCost() << std::endl;

        openSet.push(front);
        nodosGen.push_back(front.pos);
      } else if (findInPriorityQueue(openSet, front)) {
        // Si el nodo esta en A
        if (i % 2 == 0) {
          front.gCost = current.gCost + 5;
        } else {
          front.gCost = current.gCost + 7;
        }
        std::priority_queue<Nodo> tempQueue;
        bool found = false;
        while (!openSet.empty()) {
          Nodo top = openSet.top();
          openSet.pop();
          if (top == front) {
            found = true;
            if (front.gCost < top.gCost) {
              top.gCost = front.gCost;
              parentMap[top.pos] = current.pos;
              //std::cout << "Nodo actualizado: " << top.pos.first << "," << top.pos.second << " gCost: " << top.gCost << " hCost: " << top.hCost << " fCost: " << top.fCost() << std::endl;
            }
          }
          tempQueue.push(top);
        }
        openSet = tempQueue;
        if (!found) {
          openSet.push(front);
        }
      }
    }

  
    
  }
  output += "No existe camino\n";
  return output;

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

std::string Laberinto::Print(std::set<Position> pathSet) const {
  std::string output = "\nSolucion: \n";
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < columns_; j++) {
      Position current = Position(i, j);
      if (pathSet.count(current) && map_[i][j] != 4) {
        output += "* ";
      } else {
        output += std::to_string(map_[i][j]) + " ";
      }
    }
    output += "\n";
  } 
  return output;
}

std::ostream& operator<<(std::ostream& os, const Laberinto& laberinto) {
  os << laberinto.Print();
  os << std::endl;
  return os;
}

