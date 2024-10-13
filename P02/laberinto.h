#include <iostream>
#include <vector>
#include <set>
#include <functional>

#ifndef LABERINTO_H
#define LEBERINTO_H

typedef std::pair<int, int> Position;
typedef std::function<int(int, int, int, int)> HFunction;

int Manhattan(int x1, int y1, int x2, int y2);
int ManhattanV2(int x1, int y1, int x2, int y2);

class Laberinto
{
  public:
    Laberinto(const char*, HFunction hfunc = Manhattan);   // constructor recibe fichero

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
    HFunction hFunction_;
    
};

#endif