#include <vector>
#include <string>
#include <iostream>

typedef std::vector<std::vector<int>> MatrixInt;
class Board {

    int M_; //Ancho
    int N_; //Alto
    MatrixInt MatrixBoard_; //Un 0 es un espacio, un 1 es un muro, un 2 es obstáculo, un 3 la posición inicial del coche, un 4 la meta.

public:

    Board();
    Board(std::string);
    ~Board();
    
    int GetM() const;
    int GetN() const;

    void Write(std::ostream &os) const;
};