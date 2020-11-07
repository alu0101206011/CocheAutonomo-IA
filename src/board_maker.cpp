#include "../include/board_maker.hpp"

BoardMakerFrontend::BoardMakerFrontend() {}
BoardMakerFrontend::~BoardMakerFrontend() {}


void BoardMakerFrontend::Menu(){
    std::string file;
    int option;
    do {
        system("clear");
        std::cout << "Bienvenido al menú de creación de tableros.\n";
        std::cout << "Hay diferentes opciones: "; //Poner opciones
        std::cin >> option;
        std::string filename;
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
                std::cerr << "Se ha introducido una opción incorrecta\n";
                break;
        }
    } while (option != 5);
}

void BoardMakerFrontend::CreateNewMap(std::string &FileName) {

    std::ifstream reader(FileName);
    if (reader) {
        std::cout << "El fichero ya existe\n"
                  << "¿Quiere sobreescribir? Seleccione [s]i [n]o: ";
        char election;
        std::cin >> election;
        do {
            switch (election) {
            case 's':
                break;
            case 'n':
                return;
            default:
                std::cout << "Se ha escogido una opción no válida" << std::endl;
                break;
            }
        } while (election != 's' && election != 'n');
        reader.close();
    }
    
       
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
    std::cout << "Su matriz actualmente es una (" << map.GetN() + 2 << "x" << map.GetM() + 2 << ") y es asi: \n";
    map.Write(std::cout, terminalicons);

    char option;
    do {
        std::cout << "¿Qué desea introducir? [c]oche [o]bstaculo [s]alida [n]ada\n";
        std::cin >> option;

        switch (option) {
            case 'c': 
                {
                std::cout << "Ha entrado en coche.\n";
                int counter = 0;
                for (int i = 1; i < map.GetN(); i++) { 
                    for (int j = 1; j < map.GetM(); j++) { 
                        if (map.GetState(j,i) == Car && counter == 0) {
                            std::cout << "Ya existe un coche. Se encuentra en la posición (" << j << "," << i << ")" << std::endl;
                            std::cout << "¿Desea modificarlo? Seleccione [s]i [n]o: ";
                            char election = '\0';
                            std::cin >> election;
                            do {
                                switch (election) {
                                case 's':
                                    map.ChangeState(j,i,ClearPath);
                                    IntroducePos(Car, map);
                                    counter++;
                                    break;
                                case 'n':
                                    counter++;
                                    break;
                                default:
                                    std::cout << "Se ha escogido una opción no válida" << std::endl;
                                    break;
                                }
                            } while (election != 's' && election != 'n');
                        }
                    }
                }
                if (counter == 0)
                    IntroducePos(Car, map);
                map.Write(std::cout, terminalicons);
                break;
                }
            case 'o':
                std::cout << "Ha entrado en obstaculo.\n";
                std::cout << "¿Dónde desea introducir el obstáculo?" << std::endl;
                IntroducePos(Obstacle,map);
                map.Write(std::cout, terminalicons);
                break;
            case 's':
                {
                int counter = 0;
                std::cout << "Ha entrado en salida.\n";
                for (int i = 0; i < map.GetN() + 1; i++) { 
                    for (int j = 0; j < map.GetM() + 1; j++) { 
                        if(i == 0 || i == map.GetN() + 1 || j == 0 || j == map.GetM() + 1) {
                            if (map.GetState(j,i) == Finish && counter == 0) {
                                std::cout << "Ya existe una salida. Se encuentra en la posición (" << j << "," << i << ")" << std::endl;
                                std::cout << "¿Desea modificarlo? Seleccione [s]i [n]o: ";
                                char election;
                                std::cin >> election;
                                do {
                                    switch (election)
                                    {
                                    case 's':
                                        map.ChangeState(j,i,Wall);
                                        IntroducePos(Finish, map);
                                        counter++;
                                        break;
                                    case 'n':
                                        counter++;
                                        break;
                                    default:
                                        std::cout << "Se ha escogido una opción no válida" << std::endl;
                                        break;
                                    }
                                } while (election != 's' && election != 'n');
                            }
                        }
                    }
                }
                if (counter == 0)
                    IntroducePos(Finish, map);
                map.Write(std::cout, terminalicons);                
                break;
                }
            case 'n':
                break;
            default:
                std::cout << "Argumento invalido: escriba 'c' 'o' 'n' si quiere coche, obstaculo o nada\n";
                break; 
        }
    } while (option != 'n');

    std::ofstream mapfile;
    mapfile.open(FileName); 
    
    map.Write(mapfile,file);
    mapfile.close();
}

void BoardMakerFrontend::IntroducePos(state newstate, Board& map) {
    int x = 0, y = 0;
    do {
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
        if (x < 0 || y < 0 || x > (map.GetN() + 2) || y > (map.GetM() + 2))
            std::cerr << "La matriz tiene que estar entre:\n"
                      << "x = [0] a [" << map.GetN() + 1 << "]\n" 
                      << "y = [0] a [" << map.GetM() + 1 << "]\n";
    } while (x < 0 || y < 0 || x > (map.GetN() + 2) || y > (map.GetM() + 2));
    if (map.GetState(x,y) != ClearPath) {
        std::cout << "La posición indicada está ocupada por ";
        if (map.GetState(x,y) == Obstacle) {
            std::cout << "un obstáculo\n";
        } else if (map.GetState(x,y) == Car) {
            std::cout << "un coche\n";
        } else if (map.GetState(x,y) == Finish) {
            std::cout << "una salida\n";
        } else if (map.GetState(x,y) == Wall) {
            std::cout << "una pared\n";
        }  
        if (map.GetState(x,y) == Wall && newstate != Finish) {
            std::cerr << "No se puede colocar en esta posición\n";
            return;
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
                std::cout << "Ha elegido no sobrescribir\n";
                return;
            default:
                std::cout << "Se ha escogido una opción no válida" << std::endl;
                break;
            }
        } while (election != 's' && election != 'n');
    }
    if (newstate == Finish) {
        if ((x == 0 && y == 0) || (x == 0 && y == map.GetM() + 1) || 
            (x == map.GetN() + 1 && y == 0 ) || (x == map.GetN() + 1 && y == map.GetM() + 1 )) {
            std::cerr << "La salida no puede ser una esquina\n";
            return;
        }
        if(x == 0 || x == map.GetN() + 1 || y == 0 || y == map.GetM() + 1) {
            map.ChangeState(x,y,newstate);
        } else {
            std::cerr << "Se tiene que colocar en una pared\n";
        }
    }
    if (newstate == Obstacle || newstate == Car || newstate == ClearPath)  
        if(x != 0 && x != map.GetN() + 1 && y != 0 && y != map.GetM() + 1)
            map.ChangeState(x,y,newstate);
}


/* 12 12
if (i = 0 )
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