#include "../include/board_maker.hpp"
//#include "../include/board.hpp"

void board_maker(){
    std::string file;
    int option;
    std::cin >> option;
    std::string filename;

    while (option != 5) {
        switch (option) {
            case 1:
                /* Crear Nuevo Mapa */
                std::cout << "Introduzca el nombre del mapa: ";
                std::cin >> filename;
                CreateNewMap(filename);
                ModifyMap(filename);
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

void CreateNewMap(std::string &FileName) {
    std::ofstream mapfile;
    mapfile.open(FileName);
    int height, wide;
    std::cout << "¿Qué altura debe tener el tablero? ";
    std::cin >> height;
    height+=2;
    std::cout << "¿Qué anchura debe tener el tablero? ";
    std::cin >> wide;
    wide+=2;
    mapfile << wide << " " << height << std::endl;
    std::vector<std::vector<int>> map(wide, std::vector<int>(height,0));

    for (int i = 0; i < wide; i++) {
        map[i][0] = 1;
        map[i][height-1] = 1;
    }
    for (int i = 0; i < height; i++) {
        map[0][i] = 1;
        map[wide-1][i] = 1;
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < wide; j++) {
            mapfile << map[j][i];
            if (j != wide - 1) {
                mapfile << " ";
            }
        }
        if (i != height - 1) {
            mapfile << std::endl;
        }
    }
    mapfile.close();
}

void ModifyMap(std::string &FileName) {
    
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