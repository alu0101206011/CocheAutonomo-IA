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


