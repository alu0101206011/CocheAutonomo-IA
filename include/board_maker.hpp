#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "board.hpp"

class BoardMakerFrontend {    
    
    public:
    BoardMakerFrontend();
    ~BoardMakerFrontend();


    void Menu();
    void CreateNewMap(std::string&);
    void ModifyMap(std::string&);
    void IntroducePos(state,Board&);

};


