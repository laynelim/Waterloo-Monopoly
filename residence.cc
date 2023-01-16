#include <string>
#include <iostream>
#include "square.h"
#include "property.h"
#include "residence.h"
#include "player.h"
using namespace std;

Residence::Residence(string name, int position, int purchaseCost) : Property{name, position, purchaseCost}{}

Residence::~Residence(){}

int Residence::calcRent(){
  int numberOwnedRez = getOwner()->getResidence();
  cout << "Owner has " << numberOwnedRez << " residence(s)." << endl;
  if (numberOwnedRez == 1){
    return 25;
  } else if (numberOwnedRez == 2){
    return 50;
  } else if (numberOwnedRez == 3){
    return 100;
  } else if (numberOwnedRez == 4){
    return 200;
  } else {
    return 25;
  }
}

void Residence::squareAction(Player *player){
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
            player->addResidence();
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
    int r = calcRent();
    string o = getOwner()->getName();
    cout << getName() << " belongs to " << o << ". You need to pay $" << r << " in rent." << endl;
    if (r > player->getMoney()){
      string response;
      cout << "Oh no! You don't have enough money to pay the rent" << endl;
      while (true){
        cout << "Respond with 'bankrupt' to declare bankruptcy" << endl;
        cin >> response;
        if (response == "bankrupt"){
          player->BankruptOwePlayer(getOwner());
          break;
        }
      }        
    } else {
      cout << "You paid $" << r << " rent to " << o << endl;
      player->payPlayer(r, getOwner());
    }   

  } else if (getOwner() == player){
    cout << getName() << " belongs to you." << endl;
  }
}


