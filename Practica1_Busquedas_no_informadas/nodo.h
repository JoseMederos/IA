#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <queue>

#ifndef NODO
#define NODO

class Nodo {
  public:
    Nodo() : indice_(0), parent_(nullptr) {}
    Nodo(int indice, Nodo* parent) : indice_(indice), parent_(parent) {}

    void SetIndice(int indice);
    void SetParent(Nodo* parent);

    int GetIndice() const;
    Nodo* GetParent() const;

    bool CheckBranch(int indice);

    Nodo& operator=(const Nodo& other);

  private:
    int indice_;
    Nodo* parent_;
};

#endif

