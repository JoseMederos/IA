#pragma once

#include <iostream>
#include <vector>

class Nodo {
  public:

  private:
    std::vector<Nodo> sucesores_;
    int padre_;
};