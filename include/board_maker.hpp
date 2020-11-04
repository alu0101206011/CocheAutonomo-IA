#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "board.hpp"

class BoardMakerFrontend {    
    
    public:
    
    void Menu();
    void CreateNewMap(std::string&);
    void ModifyMap(std::string&);

};

int IntroducePos(const int, const int, const int, std::vector<std::vector<int>>&);