#include <iostream>
#include <vector>
#include <set>

#ifndef LABERINTO_H
#define LEBERINTO_H

typedef std::pair<int, int> Position;


class Laberinto
{
  public:
    Laberinto(const char*);   // constructor recibe fichero

    void ChangeStart(Position);
    void ChangeEnd(Position);
    std::string Print() const;
    std::string Print(std::set<Position> pathSet) const;


    std::string AStar();

    friend std::ostream& operator<<(std::ostream&, const Laberinto&);
  private:
    std::vector<std::vector<int>> map_;
    int rows_;
    int columns_;
    Position start_;
    Position end_;
    std::string solucion_;
    
};

#endif