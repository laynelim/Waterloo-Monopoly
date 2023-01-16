#ifndef BOARD_H
#define BOARD_H
#include <string>
#include <vector>

//using std::map; 

class Dice; 
class Player;
class Square;
class Property;

class Board {   
  Square * board[40];
  Player * players[6]; 

  Dice * dice; 
  //int maxCups = 4;
  int totalCups;
  Player * curPlayer;
  int numOfPlayers;
  bool hasRolled;
  bool gameEnded;


  public: 
    Board();
    ~Board();
    void newGame();  
    void loadGame(std::string loadedFile);
    void saveGame(std::string saveFile);
    void displayBoard(); 
    int getCups(); 
    bool gethasRolled();
    void roll(); 
    void roll(int dice1, int dice2); 
    void next();
    Square *getSquare(int pos);
    void assets();
    void all();
    void gameContinue(); 
    bool gameOver();
    void improvementSell(Property * property); 
    void propertySell(Property * property);
    void propertyImprove(Property * property);
};


#endif  
