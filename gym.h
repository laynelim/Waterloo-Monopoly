#ifndef GYM_H
#define GYM_H

#include <string>
#include "property.h"

class Gym: public Property {
  
  public:
    Gym(std::string name, int position, int purchaseCost);
    ~Gym();
    int calcFee();
    void squareAction(Player *player) override;
};

#endif
