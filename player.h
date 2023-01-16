#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include <vector>
#include "academic.h"
#include "residence.h"
#include "gym.h"

class Property;
class Square;

class Player {
    std::string name;
    char symbol;
    int money;
    int squarePosition;
    int playerIndex;
    int numCups;
    Property * properties[40];
    bool atTims = false;
    bool bankrupt = false;
    int numResidence = 0;
    int numGym = 0;
    int numTimsLine = 0;
    int doubles = 0;
    int bid = 0;
    int arts1 = 0;
    int arts2 = 0;
    int eng = 0;
    int health = 0;
    int env = 0;
    int sci1 = 0;
    int sci2 = 0; 
    int math = 0;

  public:
    Player(std::string name, char symbol, int money, int squarePosition, int playerIndex, int numCups);
    ~Player();
    std::string getName();
    void setName(std::string name);
    char getSymbol(); 
    void setSymbol(char symbol); 
    int getPlayerIndex(); 
    void setPlayerIndex(int playerIndex); 
    void addMoney(int money); 
    void payBank(int money);
    void payPlayer(int money, Player *player);
    int getMoney();
    void addProperty(Property *property);
    void removeProperty(Property *property);
    Property * getProperty();
    void addResidence();
    void removeResidence();
    int getResidence(); 
    void addGym();
    void removeGym();
    int getGym();
    void setSquarePosition(int position);    
    int getSquarePosition();
    bool hasMonopoly(std::string monopolyBlock);
    void BankruptOwePlayer(Player *giveto); 
    void BankruptOweBank(); 
    bool isBankrupt(); 
    void setCup(int c);
    int getCup();
    void addCup();
    void removeCup(); 
    bool isAtTims();
    void setAtTims(bool state);
    int turnsAtTims();
    int placeBid(int amount);
    void withdrawBid();
    int getNumberDoubles();
    void changeNumberDouble();
    int netWorth();
    int mortgagedAssetsWorth();
    void trade(Player * player, Property * give, Property * receive);
    void trade(Player * player, int give, Property * receive);
    void trade(Player * player, Property * give, int receive);
  
};

#endif
