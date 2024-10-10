#include <iostream>
#include <vector>

#ifndef LABERINTO_H
#define LEBERINTO_H

typedef std::pair<int, int> Position;


class Laberinto
{
  public:
    Laberinto(const char*);   // constructor recibe fichero
    std::string Print() const;

    void AStar();

    friend std::ostream& operator<<(std::ostream&, const Laberinto&);
  private:
    std::vector<std::vector<int>> map_;
    int rows_;
    int columns_;
    Position start_;
    Position end_;
    
};

#endif