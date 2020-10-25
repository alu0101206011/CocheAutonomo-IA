#include "../include/board_maker.hpp"
//#include "../include/board.hpp"

#include <iostream>
#include <string>

void board_maker(){
    std::cout << "HOLA" << std::endl;
    int option;
    std::cin >> option;

    while (option != 5) {
        switch (option) {
            case 1:
                /* Crear Nuevo Mapa */
                break;
            case 2:
                /* Modificar Mapa */
                break;
            case 3:
                /* Modificar copia de un Mapa */
                break;
            case 4:
                /* Borrar Mapa */
                break;    
            case 5:
                /* Salir */
                break;
            default:
                break;
        }
    }
}

void CreateNewMap(std::string FileName){

}



/* 12 12
1 8 1 1 1 1 1 1 1 1 1 1
1 0 0 0 0 0 1 1 0 0 0 1
1 1 0 0 0 0 0 1 0 1 0 1
1 1 1 0 1 0 0 0 1 1 0 1
1 0 1 0 0 0 1 0 0 1 0 1
1 1 1 1 0 1 1 1 0 1 0 1
1 0 1 0 0 0 1 1 0 0 1 1
1 1 1 1 1 0 1 1 0 1 0 1
1 1 0 0 0 0 0 0 0 1 1 1
1 0 0 0 0 0 1 1 0 0 0 1
1 1 1 0 1 1 0 0 1 1 0 9
1 1 1 1 1 1 1 1 1 1 1 1 */