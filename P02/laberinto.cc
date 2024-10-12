#include <iostream>
#include <fstream>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include "laberinto.h"

struct Nodo {
  Position pos;
  int gCost; // Costo desde el inicio hasta este nodo
  int hCost; // Costo estimado desde este nodo hasta el objetivo
  Position parentPos;
  int fCost() const { return gCost + hCost; }
  bool operator<(const Nodo& other) const { return fCost() > other.fCost(); }
  bool operator==(const Nodo& other) const {
    return pos == other.pos; 
  }
};

int Manhattan(int x1, int y1, int x2, int y2) {
  return (abs(x2 - x1) + abs(y2 - y1)) * 3;
}

int ManhattanV2(int x1, int y1, int x2, int y2) {
  return (abs(x2 - x1) + abs(y2 - y1)) * 4;
}

// function to search priority queue
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
std::string Laberinto::AStar() {
  Nodo startNode = {start_, 0, ManhattanV2(start_.first, start_.second, end_.first, end_.second), {-1, -1}};
  std::string output = "";
  std::priority_queue<Nodo> openSet;
  std::set<Position> closedSet;
  std::map<Position, Position> parentMap;
  openSet.push(startNode);

  int interation = 0;

    Nodo current;
  while (!openSet.empty()) {
    interation++;
    if (interation == 1) {
      output += "\nIteracion: " + std::to_string(interation) + " Nodo actual: " + "\n";
    } else {
      output += "\nIteracion: " + std::to_string(interation) + " Nodo actual: " + std::to_string(current.pos.first) + "," + std::to_string(current.pos.second) + "\n";
    }
    output += "OpenSet:\n";

    std::priority_queue<Nodo> tempQueue;
    while (!openSet.empty()) {
      Nodo top = openSet.top();
      openSet.pop();
      output += "  Nodo: " + std::to_string(top.pos.first) + "," + std::to_string(top.pos.second) + "\n";
      tempQueue.push(top);
    }
    openSet = tempQueue;
    output += "ClosedSet: \n";
    for (auto it = closedSet.begin(); it != closedSet.end(); it++) {
      output+= "  Nodo: " + std::to_string(it->first) + "," + std::to_string(it->second) + "\n";
    }
    
    // Selecciona el nodo de menor cose f(n)
    current = openSet.top();
    openSet.pop();



    if (current.pos == end_) {
      output += "\nIteracion: " + std::to_string(interation) + " Nodo actual: " + std::to_string(current.pos.first) + "," + std::to_string(current.pos.second) + "\n";


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
      // coste del camino
      output += "Coste del camino: " + std::to_string(current.gCost) + "\n";
      output = solucion_ + output;
      return output;
    }

    // Se inserta en los nodos cerrados
    closedSet.insert(current.pos);

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
        //print the values going into Manhattan function and the result
        if (i % 2 == 0) {
          front.gCost = current.gCost + 5;
        } else {
          front.gCost = current.gCost + 7;
        }
        
        front.hCost = ManhattanV2(front.pos.first, front.pos.second, end_.first, end_.second);
        parentMap[front.pos] = current.pos;

        //std::cout << "Nodo insertado: " << front.pos.first << "," << front.pos.second << " gCost: " << front.gCost << " hCost: " << front.hCost << " fCost: " << front.fCost() << std::endl;

        openSet.push(front);
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

