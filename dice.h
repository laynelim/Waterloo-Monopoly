#ifndef _DICE_H_ 
#define _DICE_H_ 

//#include <cstdlib> 
//#include "time.h"

class Dice { 
    int dice1, dice2; 
    bool isDouble; 

  public: 
    Dice();
    ~Dice();
    void rollDice(); 
    bool doubleCheck();
    int getDice1(); 
    int getDice2();
    int getSum();
    void setDouble(bool state);

};


#endif
