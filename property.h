#ifndef PROPERTY_H
#define PROPERTY_H

#include <string>
#include "square.h"

class Player;

class Property : public Square {
    Player * owner;
    int purchaseCost;
    int improvementCount;
    bool mortgaged;
  public:
    Property(std::string name, int position, int purchaseCost);
    ~Property();
    void setOwner(Player *player);
    Player * getOwner();
    int getPurchaseCost();
    friend bool operator==(Property& p1, Property& p2);
    char propertyType();
    virtual void squareAction(Player * p)=0;
    void mortgage();
    void unmortgage();
    bool isMortgaged();
    void setMortgaged(bool state);
    void auction();
    void incImprovementCount();
    void decImprovementCount();
    void setImprovementCount(int count);
    int getImprovementCount();
    void printImprovements();
    std::string whichMonopolyBlock();
};

#endif
