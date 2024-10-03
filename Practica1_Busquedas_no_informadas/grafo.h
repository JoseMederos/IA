#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <queue>

#ifndef GRAFO
#define GRAFO

class Grafo {
  public:
    Grafo() {};
    Grafo(int vertices) { 
      vertices_ = vertices;
      costes_.resize(vertices, std::vector<int>(vertices, 0));
    }

    void Print() {
      for (size_t i = 0; i < costes_.size(); i++) {
        for (size_t j = 0; j < costes_.size(); j++) {
          std::cout << costes_[i][j] << " ";
        }
        std::cout << std::endl;
      }
    }
    void AddCosts(std::string filename, std::ostream& output);
    int GetVertices() const;
    std::vector<std::vector<int>> GetCostes() const;
    bool BFS_search(int start, int goal, std::ofstream& output);
    bool DFS_search(int start, int goal, std::ofstream& output);
    bool DFS(std::stack<int>& path, std::stack<int>& generados, std::stack<int>& inspeccionados, std::vector<bool>& visited, int goal, int& coste_total, int& iteracion, std::ostream& output);
    void PrintProgress(const std::stack<int>& generados, const std::stack<int>& inspeccionados, int& iteracion, std::ostream& output) const;

  private:
    std::vector<std::vector<int>> costes_;
    int vertices_;
};

#endif

