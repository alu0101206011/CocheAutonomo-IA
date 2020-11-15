/// Clase Board
///
/// @brief clase utilizada como creadora de mapas.
/// Todos sus metodos estan destinados a la creacion, 
/// modificacion, eliminacion y visualizacion de mapas
/// usando ficheros y la clase board como herramienta
///
/// @date 15 Nov 2020
/// 
/// Autores: 
/// Jorge Niebla Núñez <alu0101215457@ull.edu.es>
/// Anabel Díaz Labrador <alu0101206011@ull.edu.es>
/// Jaime Pablo Pérez Moro <alu0101278919@ull.edu.es>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <dirent.h> 
#include "board.hpp"

class BoardMakerFrontend {   
    
    public:
    writemode write_style_; 

    BoardMakerFrontend();
    ~BoardMakerFrontend();

    void Menu();
    void CreateNewMap(std::string);
    void ModifyMap(std::string);
    void IntroducePos(state,Board&);
    void CopyMap(std::string,std::string);
    void Randomize(std::string);
    void ShowMap(std::string,std::ostream&);
    void ListMaps();
    void DeleteMap(std::string);
    void ChangeWMode();

    private:
    bool CheckMap(std::string);
    bool CheckName(std::string);
};


