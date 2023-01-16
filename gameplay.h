#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <string>
 
class Board;
class Player;

class Gameplay{

    Board * b;
    bool test = false; 

  public :
    Gameplay();
    ~Gameplay();
    void newGame();
    void saveGame(std::string saveFile);
    void loadGame(std::string loadedFile);
    void playGame();
    void setTest();
};

#endif
