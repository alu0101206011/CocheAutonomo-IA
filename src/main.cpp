#include "../include/board_maker.hpp"
#include "../include/board.hpp"
#include "../include/gps.hpp"

#include <iostream>

int main () {
    char option;
    bool terminal_icons;
    writemode write_mode_choose;
    do {
        system("clear");
        std::cout << "Bienvenido al simulador de coche autonomo.\n"
                << "Para empezar, ¿desea ver iconos en la terminal? Seleccione [s]i o [n]o\n";
        std::cin >> option;
        switch (option) {
            case 's': 
                terminal_icons = true;
                write_mode_choose = terminalicons;
                break;
            case 'n':
                terminal_icons = false;
                write_mode_choose = terminalcords;
                break;  
            default: 
                std::cerr << "Se ha introducido una opción incorrecta\n\n";
                break;
        }
    } while(option != 's' && option != 'n');
    do {
    system("clear");
    std::cout << "Necesita un mapa para empezar."
              << "Tiene diferentes opciones:\n"
              << "\t[1] Entrar en el menú de creación de tableros.\n"
              << "\t[2] Seleccionar mapa para empezar la simulación.\n"
              << "\t[3] Salir.\n"
              << "Escoja una opcion: "; 
    std::cin >> option;
    std::string filename;
        switch (option) {
            case '1':
                {
                system("clear");
                BoardMakerFrontend obj;
                if (terminal_icons) {
                    obj.write_style_ = terminalicons;
                } else {
                    obj.write_style_ = terminalcords;
                }
                obj.Menu();
                }
                break;
            case '2':
                {
                system("clear");
                std::cout << "Mapas disponibles: \n";
                system("ls boards/");
                std::cout << "\nIntroduzca el nombre del mapa: ";
                std::cin >> filename;
                Board map("boards/" + filename);
                
                std::cout << "El mapa selecionado ha sido: " << filename << "\n";
                map.Write(std::cout, write_mode_choose);
                
                GPS car(map);
                std::cout << "¿Que función heuristica desea introducir?\n"
                          << "\t[1] Euclidea.\n"
                          << "\t[2] Manhattan.\n"
                          << "Escoja una opcion: "; 
                std::cin >> option;
                system("clear");
                do {
                    switch (option) {
                        case '1':
                            if (car.get_map().GetFinish() && car.get_map().GetCar()) {
                                if (car.AStarSearch(Euclidean))
                                    std::cout << "Se ha encontrado una salida ->\n"; 
                                else 
                                    std::cout << "No se ha encontrado una salida!\n";
                            } else {
                                std::cout << "Este mapa no tiene coche o final.\nSe cancela la búsqueda.\n";
                            }
                            break;
                        case '2':  
                            if (car.get_map().GetFinish() && car.get_map().GetCar()) {
                                if (car.AStarSearch(Manhattan))
                                    std::cout << "Se ha encontrado una salida ->\n"; 
                                else 
                                std::cout << "No se ha encontrado una salida!\n";   
                            } else {
                                std::cout << "Este mapa no tiene coche o final.\nSe cancela la búsqueda.\n";
                            }      
                            break;
                        default:
                            std::cout << "Se ha escogido una opción no válida" << std::endl;
                            break;
                    }
                } while (option != '1' && option != '2');
                car.get_map().Write(std::cout, write_mode_choose);
                std::cout << "\nPress enter to continue."
                          << "\n------------------------------------------------------------------------------------------\n";
                std::cin.ignore(); 
                std::cin.get();
                system("clear");
                }
                break;
            case '3':
                std::cout << "\nSaliendo... \n";
                return 0;
            default:
                std::cerr << "Se ha introducido una opción incorrecta\n\n";
                std::cout << "\nPress enter to continue."
                          << "\n------------------------------------------------------------------------------------------\n";
                std::cin.ignore();
                std::cin.get();
                break;
        }
    } while (option != 3);
    return 0;
}