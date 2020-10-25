#include "board.hpp"
class Car {

    int PosCX;
    int PosCY;
    int PosFX;
    int PosFY;
    Board Map;

    //int SensorN;
    //int SensorE;
    //int SensorS;
    //int SensorW;

public:

    Car();
    Car(Board);
    ~Car();

private:

    //void CheckAround();

};