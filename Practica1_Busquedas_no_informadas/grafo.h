#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

#ifndef GRAFO
#define GRAFO

class Grafo {
  public:
    Grafo() {};
    Grafo(int vertices) { 
      vertices_ = vertices;
      costes_.resize(vertices, std::vector<int>(vertices, 0));
    }

    void AddCosts(std::string filename);
    int GetVertices() const;
    std::vector<std::vector<int>> GetCostes() const;
    bool DFS_search(int start, int goal, int& coste_total);
    bool DFS(std::stack<int>& path, std::stack<int>& generados, std::stack<int>& inspeccionados, std::vector<bool>& visited, int goal, int& coste_total, int& iteracion);
    void PrintProgress(const std::stack<int>& path, const std::stack<int>& generados, const std::stack<int>& inspeccionados, int& iteracion) const;



  private:
    std::vector<std::vector<int>> costes_;
    int vertices_;
};

#endif

