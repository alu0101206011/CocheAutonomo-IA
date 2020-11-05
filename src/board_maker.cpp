#include "../include/board_maker.hpp"

BoardMakerFrontend::BoardMakerFrontend() {}
BoardMakerFrontend::~BoardMakerFrontend() {}


void BoardMakerFrontend::Menu(){
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
                std::cout << "Introduzca el nombre del mapa: ";
                std::cin >> filename;
                ModifyMap(filename);
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

void BoardMakerFrontend::CreateNewMap(std::string &FileName) {
       
    int height, wide;
    std::cout << "¿Qué anchura debe tener el tablero? ";
    std::cin >> wide;
    std::cout << "¿Qué altura debe tener el tablero? ";
    std::cin >> height;

    Board map(wide,height);
    
    std::ofstream mapfile;
    mapfile.open(FileName);
    map.Write(mapfile,file);
    mapfile.close();
}

void BoardMakerFrontend::ModifyMap(std::string &FileName) {
    Board map(FileName);

    char option;
    do {
        std::cout << "¿Qué desea introducir? [c]oche [o]bstaculo [s]alida [n]ada\n";
        std::cin >> option;

        switch (option) {
            case 'c': 
                std::cout << "Ha entrado en coche.\n";
                for (int i = 1; i < map.GetN() + 1; i++) { 
                    for (int j = 1; j < map.GetM() + 1; j++) { 
                        if (map.GetState(j,i) == Car) {
                            std::cout << "Ya existe un coche. Se encuentra en la posición (" << j << "," << i << ")" << std::endl;
                            std::cout << "¿Desea modificarlo? Seleccione [s]i [n]o: ";
                            char election;
                            std::cin >> election;
                            do {
                                switch (election)
                                {
                                case 's':
                                    map.ChangeState(j,i,ClearPath);
                                    break;
                                case 'n':
                                    break;
                                default:
                                    std::cout << "Se ha escogido una opción no válida" << std::endl;
                                    break;
                                }
                            } while (election != 's' && election != 'n');
                        }
                    }
                }
                break;
            case 'o':
                std::cout << "Ha entrado en obstaculo.\n";
                std::cout << "¿Dónde desea introducir el obstáculo?" << std::endl;
                IntroducePos(Obstacle,map);
                break;
            case 's':
                std::cout << "Ha entrado en salida.\n";
                for (int i = 1; i < map.GetN() + 1; i++) { 
                    for (int j = 1; j < map.GetM() + 1; j++) { 
                        if (map.GetState(j,i) == Finish) {
                            std::cout << "Ya existe una salida. Se encuentra en la posición (" << j << "," << i << ")" << std::endl;
                            std::cout << "¿Desea modificarlo? Seleccione [s]i [n]o: ";
                            char election;
                            std::cin >> election;
                            do {
                                switch (election)
                                {
                                case 's':
                                    map.ChangeState(j,i,ClearPath);
                                    break;
                                case 'n':
                                    break;
                                default:
                                    std::cout << "Se ha escogido una opción no válida" << std::endl;
                                    break;
                                }
                            } while (election != 's' && election != 'n');
                        }
                    }
                }
                break;
            default:
                std::cout << "Argumento invalido: escriba 'c' 'o' 'n' si quiere coche, obstaculo o nada\n";
                break; 
        }
    } while (option != 'n');

    std::ofstream mapfile;
    mapfile.open(FileName); //CAMBIAR A TRUNCAR
    map.Write(mapfile,file);
    mapfile.close();

}

void BoardMakerFrontend::IntroducePos(state newstate,Board map) {
    int x, y;
    std::cout << "Posición X: ";
    std::cin >> x;
    if (std::cin.fail()) {
        std::cout << "Se a introducido una opción no válida" << std::endl;
        std::cout << "Introduzca la posición X otra vez: ";
        std::cin >> x;
    }
    std::cout << "Posición Y: ";
    std::cin >> y;
    if (std::cin.fail()) {
        std::cout << "Se a introducido una opción no válida" << std::endl;
        std::cout << "Introduzca la posición Y otra vez: ";
        std::cin >> x;
    }
    if (map.GetState(x,y) != ClearPath && map.GetState(x,y) != newstate) {
        std::cout << "La posición indicada está ocupada por ";
        if (map.GetState(x,y) == Obstacle) {
            std::cout << "un obstáculo";
        } else if (map.GetState(x,y) == Car) {
            std::cout << "un coche";
        } else if (map.GetState(x,y) == Finish) {
            std::cout << "una salida";
        }
        std::cout << "¿Desea sobrescribir la posición? Seleccione [s]í [n]o: ";
        char election;
        std::cin >> election;
        do {
            switch (election)
            {
            case 's':
                break;
            case 'n':
                return;
            default:
                std::cout << "Se ha escogido una opción no válida" << std::endl;
                break;
            }
        } while (election != 's' && election != 'n');
    }
    map.ChangeState(x,y,newstate);
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