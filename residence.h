#ifndef RESIDENCE_H
#define RESIDENCE_H

#include <string>
#include "property.h"

class Residence: public Property {

  public:
    Residence(std::string name, int position, int purchaseCost);
    ~Residence();
    int calcRent();
    void squareAction(Player *player) override;
    //void setSumDice(int s) override;
};

#endif
