#ifndef ACADEMIC_H
#define ACADEMIC_H

#include <vector>
#include <string>
#include "property.h"

class Academic: public Property {
    std::string monopolyBlock;
    std::vector<int> tuitionCost;
    int improvementCost;
  public:
    Academic(std::string name, int position, int purchaseCost, std::string monopolyBlock, int improvementCost, int tuition0, int tuition1, int tuition2, int tuition3, int tuition4, int tuition5);
    ~Academic();
    std::string getMonopolyBlock();
    int getImprovementCost();
    int calcTuition();
    void squareAction(Player *player) override;

};

#endif
