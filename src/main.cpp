#include "../include/board_maker.hpp"
#include "../include/board.hpp"
#include "../include/car.hpp"

#include <iostream>

int main () {
    std::string hola = "hola.txt";

    BoardMakerFrontend Obj;

    Board map(3,3); //segmentation fault
    //Obj.CreateNewMap(hola);
    //Obj.ModifyMap(hola); 


    return 0;
}