#include "nodo.h"

void Nodo::SetIndice(int indice) {
  indice_ = indice;
}

void Nodo::SetParent(Nodo* parent) {
  parent_ = parent;
}

int Nodo::GetIndice() const {
  return indice_;
}

Nodo* Nodo::GetParent() const {
  return parent_;
}

bool Nodo::CheckBranch(int indice) {
  Nodo* aux_nodo = this;
  
  while (aux_nodo != nullptr) {
    if (aux_nodo->indice_ == indice) {
      return true;
    }
    aux_nodo = aux_nodo->parent_;
  }
  return false;
}

Nodo& Nodo::operator=(const Nodo& other) {
  if (this != &other) {
    indice_ = other.indice_;
    parent_ = other.parent_;
  }
  return *this;
}