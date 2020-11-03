#include <vector>
#include <string>
#include <iostream>

typedef std::vector<std::vector<int>> MatrixInt;
enum state {ClearPath, Wall, Obstacle, Car, Finish}; //Un 0 es un espacio, un 1 es un muro, un 2 es obstáculo, un 3 la posición inicial del coche, un 4 la meta.
class Board {

    int M_; //Ancho
    int N_; //Alto
    MatrixInt MatrixBoard_; 

public:

    Board(); //Constructor por defecto
    Board(int,int); //Pasando M y N
    Board(std::string); //Abrir de fichero
    ~Board();
    
    int GetM() const;
    int GetN() const;
    void ChangeState(int,int,state);

    void Write(std::ostream &os) const;
};