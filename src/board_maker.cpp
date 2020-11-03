#include "../include/board_maker.hpp"

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
                std::cout << "Introduzca el nombre del mapa: ";
                std::cin >> filename;
                ModifyMap(filename);
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

void BoardMakerFrontend::CreateNewMap(std::string &FileName) {
    std::ofstream mapfile;
    mapfile.open(FileName);
    
    int height, wide;
    std::cout << "¿Qué anchura debe tener el tablero? ";
    std::cin >> wide;
    std::cout << "¿Qué altura debe tener el tablero? ";
    std::cin >> height;
    Board MAP(wide,height);

    mapfile << MAP.GetM() << std::endl << MAP.GetN() << std::endl;
    std::vector<std::vector<int>> map(wide, std::vector<int>(height,0));

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
    std::ifstream mapfile(FileName);
    std::ofstream maptemp("maptemp.txt"); 
    if(!mapfile || !maptemp) {
        std::cout << "Error al abrir el archivo!" << "\n";
        exit(1);
    } 
    int wide, height;
    mapfile >> wide >> height;
    std::cout << wide << " " << height << "\n";
    std::vector<std::vector<int>> map(wide, std::vector<int>(height));
    for (int i = 0; i < height; i++)
        for (int j = 0; j < wide; j++)
            mapfile >> map[j][i];

    char change;
    do {
        std::cout << "¿Qué desea introducir? [c]oche [o]bstaculo [s]alida [n]ada\n";
        std::cin >> change;

        switch (change) {
            case 'c': 
                std::cout << "Ha entrado en coche.\n";
                for (int i = 0; i < height; i++)
                    for (int j = 0; j < wide; j++)
                        if (map[j][i] == 5) {
                            std::cout << "Ya existe un coche. Se encuentra en la posición " << j << " " << i << " .\n"
                                      << "¿Desea modificarlo? Seleccione [s]i [n]o";
                            char election;
                            std::cin >> election;
                            if (election == 's') map[j][i] = 0;
                            if (election == 'n') break;
                        }
                if (IntroducePos(wide, height, 8, map) == -1 ) break;
                break;

            case 'o':
                int election;
                std::cout << "Ha entrado en obstaculo.\n";
                do {
                    if (IntroducePos(wide, height, 1, map) == -1 ) break;
                    std::cout << "\n¿Desea introducir otro obstaculo? Pulse 0 para parar.\n";
                    std::cin >> election;
                    if (election != 1 && election != 0) { 
                        std::cout << "No ha introducido un valor correcto\n"; 
                        break;
                    }
                } while (election != 0);
                break;

            case 's':
                std::cout << "Ha entrado en salida.\n";
                for (int i = 0; i < height; i++)
                    for (int j = 0; j < wide; j++)
                        if (map[j][i] == 5) {
                            std::cout << "Ya existe una saluda. Se encuentra en la posición " << j << " " << i << " .\n"
                                      << "¿Desea modificarla? Seleccione [s]i [n]o";
                            char election;
                            std::cin >> election;
                            if (election == 's') map[j][i] = 0;
                            if (election == 'n') break;
                        }
                if (IntroducePos(wide, height, 9, map) == -1 ) break;
                break;

            default:
                std::cout << "Argumento invalido: escriba 'c' 'o' 'n' si quiere coche, obstaculo o nada\n";
                break; 
        }

    } while (change != 'n');

//Falta introducir los cambios en el fichero

    mapfile.close();
    maptemp.close();

    remove(FileName.c_str());                    // borrar el original
    rename("maptemp.txt", FileName.c_str());  // renombrar el temporal

}

int IntroducePos(const int wide, const int height, const int election, std::vector<std::vector<int>>& map) {
    int i, j;
    do {
        std::cout << "Posicion i: ";
        std::cin >> j;
        std::cout << "Posicion j: ";
        std::cin >> i;
        if (!(int)i || !(int)j) {
            std::cout << "No ha introducido un numero.\n";
            return -1;
        }
        if(i < 1 || i > wide || j < 1 || j > height)
            std::cout << "\nPosicion no valida, intentelo de nuevo. \n";
    } while(i < 1 || i > wide || j < 1 || j > height);

    map[j][i] = election;

    std::cout << "Se ha cambiado la posición satisfactoriamente.\n";
    return 0;
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