#include "../include/board_maker.hpp"

BoardMakerFrontend::BoardMakerFrontend() {}
BoardMakerFrontend::~BoardMakerFrontend() {}


void BoardMakerFrontend::Menu(){
    std::string file;
    char option;
    system("clear");
    do {
        system("clear");
        std::cout << "Bienvenido al menú de creación de tableros.\n";
        std::cout << "Hay diferentes opciones:\n"; //Poner opciones
        std::cout << "\t[1] Crear un nuevo mapa vacío.\n";
        std::cout << "\t[2] Modificar un mapa existente.\n";
        std::cout << "\t[3] Modificar una copia de un mapa existente.\n";
        std::cout << "\t[4] Crear un mapa aleatorio.\n";
        std::cout << "\t[5] Aleatorizar un mapa existente.\n";
        std::cout << "\t[6] Ver listado de mapas.\n";
        std::cout << "\t[7] Ver un mapa concreto.\n";
        std::cout << "\t[8] Borrar un mapa.\n";
        std::cout << "\t[9] Cambiar modo de visualización.\n";
        std::cout << "\t[0] Salir.\n";
        std::cout << "Escoja una opcion: "; //Poner opciones
        std::cin >> option;
        //system("clear");
        std::string filename;
        std::string newfilename;
        switch (option) {
            case '1':
                /* Crear Nuevo Mapa */
                system("clear");
                std::cout << "Se va a crear un mapa nuevo\n";
                std::cout << "Introduzca el nombre del mapa: ";
                std::cin >> filename;
                CreateNewMap(filename);
                ModifyMap(filename);
                break;
            case '2':
                /* Modificar Mapa */
                system("clear");
                std::cout << "Se va a modifcar un mapa\n";
                std::cout << "Mapas disponibles: \n";
                system("ls boards/");
                std::cout << "Introduzca el nombre del mapa: ";
                std::cin >> filename;
                ModifyMap(filename);

                break;
            case '3':
                /* Modificar copia de un Mapa */
                system("clear");
                std::cout << "Se va a modifcar una copia de un mapa\n";
                std::cout << "Mapas disponibles: \n";
                system("ls boards/");
                std::cout << "Introduzca el nombre del mapa a copiar: ";
                std::cin >> filename;
                std::cout << "Introduzca el nuevo nombre del mapa: ";
                std::cin >> newfilename;
                CopyMap(filename,newfilename);
                ModifyMap(newfilename);
                break;
            case '4':
                /* Crear un mapa aleatorio */
                system("clear");
                std::cout << "Se va a crear un mapa aleatorio\n";
                std::cout << "Introduzca el nombre del mapa: ";
                std::cin >> filename;
                CreateNewMap(filename);
                Randomize(filename);
                std::cout << "\nPress enter to continue.";
                std::cout << "\n------------------------------------------------------------------------------------------\n"; 
                std::cin.ignore();
                std::cin.get();
                system("clear");
                break;  
            case '5':
                /* Aleatorizar un mapa */
                system("clear");
                std::cout << "Se va a aleatorizar un mapa\n";
                std::cout << "Mapas disponibles: \n";
                system("ls boards/");
                std::cout << "Introduzca el nombre del mapa: ";
                std::cin >> filename;
                Randomize(filename);
                std::cout << "\nPress enter to continue.";
                std::cout << "\n------------------------------------------------------------------------------------------\n"; 
                std::cin.ignore();
                std::cin.get();
                system("clear");
                break;
            case '6':
                /* Ver listado de mapas */
                system("clear");
                ListMaps();
                break;
            case '7':
                /* Ver un mapa concreto */
                system("clear");
                std::cout << "Se va a ver un mapa concreto\n";
                std::cout << "Mapas disponibles: \n";
                system("ls boards/");
                std::cout << "Introduzca el nombre del mapa: ";
                std::cin >> filename;
                ShowMap(filename,std::cout);
                std::cout << "\nPress enter to continue.";
                std::cout << "\n------------------------------------------------------------------------------------------\n";
                std::cin.ignore();
                std::cin.get();
                system("clear");
                break;
            case '8':
                /* Borrar Mapa */
                system("clear");
                std::cout << "Se va a borrar un mapa\n";
                std::cout << "Mapas disponibles: \n";
                system("ls boards/");
                std::cout << "Introduzca el nombre del mapa a borrar: ";
                std::cin >> filename;
                CheckMap(filename);
                DeleteMap(filename);
                break;  
            case '9':
                /* Salir */
                system("clear");
                std::cout << "Se va escoger el modo de visualización";
                ChangeWMode();
                break;
            case '0':
                /* Salir */
                std::cout << "Saliendo..." << std::endl;
                std::cout << "\nPress enter to continue."
                          << "\n------------------------------------------------------------------------------------------\n"; 
                std::cin.ignore();
                std::cin.get();
                system("clear");
                break;
            default:
                std::cerr << "Se ha introducido una opción incorrecta\n\n";
                std::cout << "\nPress enter to continue."
                          << "\n------------------------------------------------------------------------------------------\n"; 
                std::cin.ignore();
                std::cin.get();
                break;
        }
        std::cout << std::endl;
    } while (option != '0');
}

void BoardMakerFrontend::CreateNewMap(std::string filename) {

    if (!CheckName(filename)) {
        return;
    }

    std::ifstream reader("boards/" + filename);
    if (reader) {
        char election;
        do {
            std::cout << "El fichero ya existe\n"
                    << "¿Quiere sobreescribir? Seleccione [s]i [n]o: ";
            std::cin >> election;            
            switch (election) {
                case 's':
                    break;
                case 'n':
                    reader.close();
                    return;
                default:
                    std::cout << "\nSe ha escogido una opción no válida" << std::endl;
                    break;
            }
        } while (election != 's' && election != 'n');
       reader.close();
    }
       
    int height, wide;
    char param;
    std::cout << "¿Qué altura debe tener el tablero? ";
    std::cin >> param;
    if (!isdigit(param)) {
        do {
            std::cout << "Introduzca una altura válida para el tablero: ";
            std::cin >> param;
        } while (!isdigit(param));
    }
    height = (int)(param - '0');
    std::cout << "¿Qué anchura debe tener el tablero? ";
    std::cin >> param;
    if (!isdigit(param)) {
        do {
            std::cout << "Introduzca una altura válida para el tablero: ";
            std::cin >> param;
        } while (!isdigit(param));
    }
    wide = (int)(param - '0');
    Board map(height,wide);
    
    std::ofstream mapfile;
    mapfile.open("boards/" + filename);
    map.Write(mapfile,file);
    mapfile.close();
}

void BoardMakerFrontend::ModifyMap(std::string filename) {
    if (!CheckName(filename)) {
        return;
    }
    Board map("boards/" + filename);
    char option;
    do {
        system("clear");
        std::cout << "Su matriz actualmente es una (" << map.GetM() << "x" << map.GetN() << ") y es asi: \n";
        map.Write(std::cout, write_style_);
        std::cout << "¿Qué desea introducir? [c]oche [o]bstaculo [s]alida [e]liminar [n]ada\n";
        std::cin >> option;

        switch (option) {
            case 'c': 
                {
                std::cout << "Ha entrado en coche.\n";
                bool car_exist = false;
                for (int i = 0; i < map.GetM(); i++) { 
                    for (int j = 0; j < map.GetN(); j++) { 
                        if (map.GetState(i,j) == Car && !car_exist) {
                            std::cout << "Ya existe un coche. Se encuentra en la posición (" << i << "," << j << ")" << std::endl;
                            std::cout << "¿Desea modificarlo? Seleccione [s]i [n]o: ";
                            char election = '\0';
                            std::cin >> election;
                            do {
                                switch (election) {
                                case 's':
                                    map.ChangeState(i,j,ClearPath);
                                    IntroducePos(Car, map);
                                    car_exist = true;
                                    break;
                                case 'n':
                                    car_exist = true;
                                    break;
                                default:
                                    std::cout << "\nSe ha escogido una opción no válida" << std::endl;
                                    break;
                                }
                            } while (election != 's' && election != 'n');
                        }
                    }
                }
                if (!car_exist)
                    IntroducePos(Car, map);
                break;
                }
            case 'o':
                std::cout << "Ha entrado en obstaculo.\n";
                std::cout << "¿Dónde desea introducir el obstáculo?" << std::endl;
                IntroducePos(Obstacle,map);
                break;
            case 's':
                {
                bool finish_exist = false;
                std::cout << "Ha entrado en salida.\n";
                for (int i = 0; i < map.GetM(); i++) { 
                    for (int j = 0; j < map.GetN(); j++) {
                        if (map.GetState(i,j) == Finish && !finish_exist) {
                            std::cout << "Ya existe una salida. Se encuentra en la posición (" << i << "," << j << ")" << std::endl;
                            std::cout << "¿Desea modificarlo? Seleccione [s]i [n]o: ";
                            char election;
                            std::cin >> election;
                            do {
                                switch (election)
                                {
                                case 's':
                                    map.ChangeState(i,j,ClearPath);
                                    IntroducePos(Finish, map); 
                                    finish_exist = true;
                                    break;
                                case 'n':
                                    finish_exist = true;
                                    break;
                                default:
                                    std::cout << "\nSe ha escogido una opción no válida" << std::endl;
                                    break;
                                }
                            } while (election != 's' && election != 'n');
                        }
                    }
                }
                if (!finish_exist)
                    IntroducePos(Finish, map); 
                }
                break;
            case 'e':
                std::cout << "Ha entrado en eliminar.\n";
                std::cout << "¿Qué posición desea eliminar?\n";
                IntroducePos(ClearPath,map);
                break;
            case 'n':
                system("clear");
                break;
            default:
                std::cout << "Argumento invalido: escriba 'c' 'o' 'n' 'e' si quiere coche, obstaculo o nada\n";
                break; 
        }
    } while (option != 'n');

    std::ofstream mapfile;
    mapfile.open("boards/" + filename); 
    map.Write(mapfile,file);
    mapfile.close();
}

void BoardMakerFrontend::IntroducePos(state newstate, Board& map) {
    int x, y;
    char param;
    do {
        std::cout << "Posición X: ";
        std::cin >> param;
        do {
            if (!std::isdigit(param)) {
                std::cout << "\nSe a introducido una opción no válida" << std::endl;
                std::cout << "Introduzca la posición X otra vez: ";
                std::cin >> param;
            }
        } while (!std::isdigit(param));
        x = (int)(param - '0');
        std::cout << "Posición Y: ";
        std::cin >> param;
        do {
            if (!std::isdigit(param)) {
                std::cout << "\nSe a introducido una opción no válida" << std::endl;
                std::cout << "Introduzca la posición Y otra vez: ";
                std::cin >> param;
            } 
        } while (!std::isdigit(param));
        y = (int)(param - '0');
        if ((x < 0) || (y < 0) || (x >= (map.GetM())) || (y >= (map.GetN())))
            std::cerr << "La posición tiene que estar entre:\n"
                      << "x = [0] a [" << map.GetN() - 1 << "]\n" 
                      << "y = [0] a [" << map.GetM() - 1 << "]\n";
    } while (x < 0 || y < 0 || x > (map.GetM() - 1) || y > (map.GetN() - 1));
    if (map.GetState(x,y) != ClearPath) {
        std::cout << "La posición indicada está ocupada por ";
        if (map.GetState(x,y) == Obstacle) {
            std::cout << "un obstáculo\n";
        } else if (map.GetState(x,y) == Car) {
            std::cout << "un coche\n";
        } else if (map.GetState(x,y) == Finish) {
            std::cout << "una salida\n";
        }
        char election;
        do {
            std::cout << "¿Desea sobrescribir la posición? Seleccione [s]í [n]o: ";
            std::cin >> election;
            switch (election) {
            case 's':
                break;
            case 'n':
                std::cout << "Ha elegido no sobrescribir\n";
                return;
            default:
                std::cout << "\nSe ha escogido una opción no válida" << std::endl;
                break;
            }
        } while (election != 's' && election != 'n');
    }
    map.ChangeState(x,y,newstate);
}

void BoardMakerFrontend::CopyMap(std::string oldname, std::string newname) {
    std::ifstream sourcefile;
    sourcefile.open("boards/" + oldname, std::ios::binary);
    std::ofstream destinyfile;
    destinyfile.open("boards/" + newname, std::ios::binary);
    destinyfile << sourcefile.rdbuf();
    sourcefile.close();
    destinyfile.close();
}

void BoardMakerFrontend::Randomize(std::string filename) {
    if (!CheckName(filename)) {
        return;
    }
    Board map("boards/" + filename);
    map.ClearMap();
    int obstacles;
    std::cout << "Introduzca el porcentaje de obstáculos que quiere: ";
    std::cin >> obstacles;
    obstacles = map.GetM() * map.GetN() * obstacles / 100;
    map.ShuffleMap(obstacles);
    std::ofstream mapfile;
    mapfile.open("boards/" + filename);
    map.Write(mapfile,file);
    map.Write(std::cout,write_style_);
    mapfile.close();
}

void BoardMakerFrontend::ShowMap(std::string filename, std::ostream& os) {
    Board map("boards/" + filename);
    map.Write(std::cout, write_style_);
}

void BoardMakerFrontend::ListMaps() {
    DIR *dr = opendir("boards/");
    if (dr == NULL) { // opendir returns NULL if couldn't open directory 
        std::cerr << "Could not open current directory" << std::endl; 
        return; 
    }
    struct dirent *de;
    std::ofstream mapfiles;
    mapfiles.open("bin/maps.lst");
    while ((de = readdir(dr)) != NULL)  {
        std::string name(de->d_name);
        if (name != "." && name != ".." )
            mapfiles << name << std::endl;
    }
    mapfiles.close();
    system("less bin/maps.lst");
    closedir(dr);
}

void BoardMakerFrontend::ChangeWMode() {
    char option;
    do {
        std::cout << "¿Cómo desea ver el mapa?\n";
        std::cout << "[i]conos ó [c]oordenadas: ";
        std::cin >> option;
        switch (option) {
        case 'i':
            write_style_ = terminalicons;
            break;
        case 'c':
            write_style_ = terminalcords;
            break;
        default:
            std::cout << "\nSe ha escogido una opción no válida" << std::endl;
            break;
        }
    } while (option != 'i' && option != 'c');
}

void BoardMakerFrontend::DeleteMap(std::string filename) {
    system(("rm -f boards/" + filename).c_str());
}

bool BoardMakerFrontend::CheckMap(std::string filename) {
    if (!CheckName(filename)) {
        return false;
    }
    std::ifstream filetocheck;
    filetocheck.open("boards/" + filename);
    if (!filetocheck) {
        std::cerr << "No se ha podido abrir el fichero" << std::endl;
        filetocheck.close();
        return false;
    }
    return true;
    //Comprobar que un fichero esté en buen estado, tipo dimensiones bien, 1 coche, 1 meta, etc.
}

bool BoardMakerFrontend::CheckName(std::string filename) {
    if (filename.find('/') != std::string::npos) {
        std::cerr << "Tu fichero tiene caracteres no válidos" << std::endl;
        return false; // found
    }
    return true;
}
