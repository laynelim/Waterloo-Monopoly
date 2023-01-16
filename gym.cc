#include <string>
#include <iostream>
#include "square.h"
#include "property.h"
#include "gym.h"
#include "player.h"
using namespace std;

Gym::Gym(string name, int position, int purchaseCost) : Property{name, position, purchaseCost}{}

Gym::~Gym(){}

//calculate the gym fee
int Gym::calcFee(){
  int ownedGyms = getOwner()->getGym();
  if (ownedGyms == 1){
    cout << "Owner owns one gym, so the fee is 4 times the sum of the dice" << endl;
    return (this->getSumDice() * 4);
  } else if (ownedGyms == 2){
    cout << "Owner owns two gyms, so the fee is 10 times the sum of the dice" << endl;
    return (getSumDice() * 10);
  } else {
    return 0;
  }
}

//action when player lands on gym
void Gym::squareAction(Player *player){
  cout << player->getName() << ", you are now at " << getName() << endl;
  
  if (getOwner() == nullptr){
    while (true){
      cout << getName() << " is on sale. Do you want to buy it for $" << getPurchaseCost() << " ? (Respond with: Y or N)" << endl;
      char response;
      cin >> response;
      if (response == 'Y' || response == 'N'){
        if (response == 'Y'){
          if (getPurchaseCost() > player->getMoney()){
            cout << "Oh no! You don't have enough money to buy " << getName() << endl;
          } else {
            cout << "You successfully bought " << getName() << endl;
            player->payBank(getPurchaseCost());
            player->addGym();
            player->addProperty(this);
            setOwner(player);
          }
        } else {
          cout << "Auction Time! (Not implemented)" << endl;
          //auction
        }
        break;
      }  
    }
    
  } else if (getOwner() != player){
    int f = calcFee();
    string o = getOwner()->getName();
    cout << getName() << " belongs to " << o << ". You need to pay $" << f << " in gym fees." << endl;
    if (f > player->getMoney()){
      string response;
      cout << "Oh no! You don't have enough money to pay the gym fees" << endl;
      while (true){
        cout << "Respond with 'bankrupt' to declare bankruptcy" << endl;
        cin >> response;
        if (response == "bankrupt"){
          player->BankruptOwePlayer(getOwner());
          break;
        }
      }     
    } else {
      cout << "You paid $" << f << " gym fees to " << o << endl;
      player->payPlayer(f, getOwner());
    }   

  } else if (getOwner() == player){
    cout << getName() << " belongs to you." << endl;
  }

}

