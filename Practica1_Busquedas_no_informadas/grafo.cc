#include "grafo.h"

void Grafo::AddCosts(std::string filename) {
  std::fstream input;
  input.open(filename);
  double lineread;
  int aristas = 0;
  input >> vertices_;
  int vertices = vertices_;
  costes_.resize(vertices, std::vector<int>(vertices, 0));
  std::cout << "Número de vertices del grafo: " << vertices << std::endl;
  for (int i = 0; i < vertices; i++) {
    for (int j = i + 1; j < vertices; j++) {
      input >> lineread;
      int cost = static_cast<int>(lineread);
      if (cost > 0) {
        costes_[i][j] = cost;
        costes_[j][i] = cost;
        aristas++;
      }
    }
  }
  std::cout << "Número de aristas del grafo: " << aristas << std::endl;
}

int Grafo::GetVertices() const {
  return vertices_;
}

std::vector<std::vector<int>> Grafo::GetCostes() const {
  return costes_;
}

bool Grafo::DFS_search(int start, int goal, int& coste_total) {
  std::stack<int> path, generados, inspeccionados;
  std::vector<bool> visited(vertices_, 0);
  path.push(start);
  generados.push(start);
  visited[start - 1] = 1;
  int iteracion = 1;

  if (DFS(path, generados, inspeccionados, visited, goal, coste_total, iteracion)) {
    std::stack<int> temp_path = path;
    std::vector<int> gen_elements;

    while (!temp_path.empty()) {
      gen_elements.push_back(temp_path.top());
      temp_path.pop();
    }

    std::cout << "Camino: ";
    for (int i = gen_elements.size() - 1; i >= 0; i--) {
      std::cout << gen_elements[i];
      if (i != 0) std::cout << " - ";
    }
    std::cout << std::endl;
    std::cout << "Costo: " << coste_total << std::endl;
    return true;
  } else {
    std::cout << "Camino no encontrado." << std::endl;
    return false;
  }

}

bool Grafo::DFS(std::stack<int>& path, std::stack<int>& generados, std::stack<int>& inspeccionados, std::vector<bool>& visited, int goal, int& coste_total, int& iteracion) {
  int current = path.top(); // current  = 6

  PrintProgress(path, generados, inspeccionados, iteracion);
  iteracion++;
  if (current == goal){
    return true;
  }

  for (int i = 0; i < vertices_; i++) {
    if (costes_[current - 1][i] != 0 && !visited[i]) {
      visited[i] = 1;
      generados.push(i + 1);
      //std::cout << "Current: " << i + 1 << std::endl;
      inspeccionados.push(path.top());
      path.push(i + 1);
      if (DFS(path, generados, inspeccionados, visited, goal, coste_total, iteracion)) {
        coste_total += costes_[current - 1][i];
        return true;
      } else {
        visited[i] = 0;
        //std::cout << "Pop: " << path.top() << std::endl;
        path.pop();
        inspeccionados.pop();
      }
    }
  }
  return false;
}

void Grafo::PrintProgress(const std::stack<int>& path, const std::stack<int>& generados, const std::stack<int>& inspeccionados, int& iteracion) const {
  std::cout << "Iteración " << iteracion << std::endl;
  
  std::stack<int> temp_path = generados;
  std::vector<int> gen_elements;

  while (!temp_path.empty()) {
    gen_elements.push_back(temp_path.top());
    temp_path.pop();
  }

  std::cout << "Nodos generados: ";
  for (int i = gen_elements.size() - 1; i >= 0; i--) {
      std::cout << gen_elements[i];
      if (i != 0) std::cout << ", ";
    }
  std::cout << std::endl;

  // inspeccionados = path?? si no en que momento se agrega el nodo final? o no se agrega?

  temp_path = path;
  std::vector<int> path_elements;
  while (!temp_path.empty()) {
    path_elements.push_back(temp_path.top());
    temp_path.pop();
  }

  std::cout << "Nodos inspeccionados: ";
  for (int i = path_elements.size() - 1; i >= 0; i--) {
      std::cout << path_elements[i];
      if (i != 0) std::cout << ", ";
    }
  std::cout << std::endl;
  std::cout << std::endl;
}