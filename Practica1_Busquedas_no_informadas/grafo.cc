#include "grafo.h"
#include "nodo.h"

void Grafo::AddCosts(std::string filename, std::ostream& output) {
  std::fstream input;
  input.open(filename);
  double lineread;
  int aristas = 0;
  input >> vertices_;
  int vertices = vertices_;
  costes_.resize(vertices, std::vector<int>(vertices, 0));
  output << "Número de vertices del grafo: " << vertices << std::endl;
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
  output << "Número de aristas del grafo: " << aristas << std::endl;
}

int Grafo::GetVertices() const {
  return vertices_;
}

std::vector<std::vector<int>> Grafo::GetCostes() const {
  return costes_;
}

void showq(std::queue<Nodo*> gq){
  std::queue<Nodo*> g = gq;
  while (!g.empty()) {
    std::cout << '\t' << g.front()->GetIndice();
    g.pop();
  }
  std::cout << '\n';
}

bool Grafo::BFS_search(int start, int goal, std::ofstream& output) {
  int coste_total = 0;
  std::stack<int> path, generados, inspeccionados;
  std::queue<Nodo*> q;
  Nodo* root = new Nodo(start, nullptr);
  q.push(root);
  int iteracion = 1;
  generados.push(start);
  
  while (!q.empty()) {
    Nodo* current = q.front();
    PrintProgress(generados, inspeccionados, iteracion, output);
    iteracion++;
    q.pop();

    if (current->GetIndice() == goal) {
      inspeccionados.push(current->GetIndice());
      PrintProgress(generados, inspeccionados, iteracion, output);
      std::vector<int> gen_elements;
      while (current != nullptr) {
        gen_elements.push_back(current->GetIndice());
        current = current->GetParent();
      }

      for (size_t i = 0; i < gen_elements.size() - 1; i++) {
        coste_total += costes_[gen_elements[i] - 1][gen_elements[i + 1] - 1];
      }
      
      output << "Camino: ";
      for (int i = gen_elements.size() - 1; i >= 0; i--) {
        output << gen_elements[i];
        if (i != 0) output << " - ";
      }
      output << std::endl;
      output << "Costo: " << coste_total << std::endl;

      return true;
    }

    for (int i = 0; i < vertices_; i++) {
      if (costes_[current->GetIndice() - 1][i] != 0 && !current->CheckBranch(i + 1)) {
        Nodo* aux = new Nodo(i + 1, current);
        q.push(aux);
        generados.push(i + 1);
      }
    }
    inspeccionados.push(current->GetIndice());
  }
  return false;
}


bool Grafo::DFS_search(int start, int goal, std::ofstream& output) {
  int coste_total = 0;
  std::stack<int> path, generados, inspeccionados;
  std::vector<bool> visited(vertices_, 0);
  path.push(start);
  generados.push(start);
  visited[start - 1] = 1;
  int iteracion = 1;

  if (DFS(path, generados, inspeccionados, visited, goal, coste_total, iteracion, output)) {
    std::stack<int> temp_path = path;
    std::vector<int> gen_elements;

    while (!temp_path.empty()) {
      gen_elements.push_back(temp_path.top());
      temp_path.pop();
    }

    output << "Camino: ";
    for (int i = gen_elements.size() - 1; i >= 0; i--) {
      output << gen_elements[i];
      if (i != 0) output << " - ";
    }
    output << std::endl;
    output << "Costo: " << coste_total << std::endl;
    return true;
  } else {
    std::cout << "Camino no encontrado." << std::endl;
    return false;
  }

}

bool Grafo::DFS(std::stack<int>& path, std::stack<int>& generados, std::stack<int>& inspeccionados, std::vector<bool>& visited, int goal, int& coste_total, int& iteracion , std::ostream& output) {
  int current = path.top(); // current  = 6
  //std::cout << "Current: " << current << std::endl;

  PrintProgress(generados, inspeccionados, iteracion, output);
  iteracion++;
  
  for (int j = 0; j < vertices_; j++) {
    if (costes_[current - 1][j] && !visited[j]) {
      generados.push(j + 1);
    }
  }

      inspeccionados.push(path.top());
  if (current == goal){
    PrintProgress(generados, inspeccionados, iteracion, output);
    return true;
  }
  for (int i = 0; i < vertices_; i++) {
    if (costes_[current - 1][i] != 0 && !visited[i]) {
      visited[i] = 1;
      //generados.push(i + 1);
      //std::cout << "-> generados push: " << i + 1 << std::endl;
      //std::cout << "-> inspeccionados push: " << path.top() << std::endl;
      path.push(i + 1);
      //std::cout << "-> path push: " << i + 1 << std::endl;
      if (DFS(path, generados, inspeccionados, visited, goal, coste_total, iteracion, output)) {
        coste_total += costes_[current - 1][i];
        return true;
      } else {
        visited[i] = 0;
        //std::cout << "-> Pop: " << path.top() << std::endl;
        path.pop();
        
        //inspeccionados.pop();
      }
    }
  }
  return false;
}

void Grafo::PrintProgress(const std::stack<int>& generados, const std::stack<int>& inspeccionados, int& iteracion, std::ostream& output) const {
  output << "___________________________________________________________________________________________________________________________________" << std::endl;
  output << std::endl;
  output << "Iteración " << iteracion << std::endl;
  
  std::stack<int> temp_path = generados;
  std::vector<int> gen_elements;

  while (!temp_path.empty()) {
    gen_elements.push_back(temp_path.top());
    temp_path.pop();
  }

  output << "Nodos generados: ";
  for (int i = gen_elements.size() - 1; i >= 0; i--) {
      output << gen_elements[i];
      if (i != 0) output << ", ";
    }
  output << std::endl;
  // inspeccionados = path?? si no en que momento se agrega el nodo final? o no se agrega?

  temp_path = inspeccionados;
  std::vector<int> path_elements;
  while (!temp_path.empty()) {
    path_elements.push_back(temp_path.top());
    temp_path.pop();
  }

  output << "Nodos inspeccionados: ";
  for (int i = path_elements.size() - 1; i >= 0; i--) {
      output << path_elements[i];
      if (i != 0) output << ", ";
    }
  output << std::endl;
}