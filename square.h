#ifndef SQUARE_H
#define SQUARE_H
 
#include "board.h"
#include <string>
#include <vector>

class Player;

class Square{
    std::string name;
    int position;
    std::vector<Player> players;
    int sumDice;
  public:
    Square(std::string name, int position);
    virtual ~Square();
    std::string getName();
    std::vector<Player> getPlayers();
    void addPlayer(Player * player);
    void removePlayer(Player * player);
    int getPosition();
    virtual void squareAction(Player *player)=0;
    void printPlayers();
    void setSumDice(int s);
    int getSumDice();
    
};

#endif
