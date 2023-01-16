#include <string>
#include <iostream>
#include <iomanip>
#include "square.h"
#include "property.h"
#include "academic.h"
#include "player.h"
#include "board.h"
using namespace std;

Academic::Academic(string name, int position, int purchaseCost, string monopolyBlock, int improvementCost, int tuition0, int tuition1, int tuition2, int tuition3, int tuition4, int tuition5) 
  : Property{name, position, purchaseCost},
    improvementCost{improvementCost}, 
    monopolyBlock{monopolyBlock} 
{
    tuitionCost.push_back(tuition0);
    tuitionCost.push_back(tuition1);
    tuitionCost.push_back(tuition2);
    tuitionCost.push_back(tuition3);
    tuitionCost.push_back(tuition4);
    tuitionCost.push_back(tuition5);
}

Academic::~Academic(){}

string Academic::getMonopolyBlock(){
  return monopolyBlock;
}

int Academic::getImprovementCost(){
  return improvementCost;
}

int Academic::calcTuition(){
  if (getOwner()->hasMonopoly(monopolyBlock) && getImprovementCount() == 0) {
    return tuitionCost[0] * 2;
  } else {
    return tuitionCost[getImprovementCount()];
  }
}

void Academic::squareAction(Player *player){
  cout << player->getName() << ", you are now at " << getName() << endl;
  
  if (getOwner() == nullptr){
    while (true){
      cout << getName() << " is on sale. Do you want to buy it for $" << getPurchaseCost() << " ? (Respond with: Y or N)" << endl;
      string response = "";
      cin >> response;
      if (response == "Y" || response == "N"){
        if (response == "Y"){
          if (getPurchaseCost() > player->getMoney()){
            cout << "Oh no! You don't have enough money to buy " << getName() << endl;
          } else {
            cout << "You successfully bought " << getName() << endl;
            player->payBank(getPurchaseCost());
            player->addProperty(this);
            setOwner(player);
          }
        } else {
          cout << "Auction Time! (Not implemented)" << endl;
          //auction
        }
        break;
      } else {
        cout << "Invalid response" << endl;
        continue;
      }
    }
    
  } else if (getOwner() != player){
    int t = calcTuition();
    string o = getOwner()->getName();
    cout << getName() << " belongs to " << o << ". You need to pay $" << t << " in tuition." << endl;
    if (t > player->getMoney()){
      string response;
      cout << "Oh no! You don't have enough money to pay tuition" << endl;
      while (true){
        cout << "Respond with 'bankrupt' to declare bankruptcy" << endl;
        cin >> response;
        if (response == "bankrupt") {
          player->BankruptOwePlayer(getOwner()); 
          break;
        }
      }     
    } else {
      cout << "You paid $" << t << " tuition to " << o << endl;
      player->payPlayer(t, getOwner());
    }   

  } else if (getOwner() == player){
    cout << getName() << " belongs to you." << endl;
  }
}

