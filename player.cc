#include "player.h"
#include "property.h"
#include "square.h"
using namespace std;

Player::Player(std::string name, char symbol, int money, int squarePosition, int playerIndex, int numCups)
  : name{name},
    symbol{symbol},
    money{money},
    squarePosition{squarePosition},
    playerIndex{playerIndex},
    numCups{numCups}
{
  for(int i = 0; i < 40; i++) {
    properties[i] = nullptr;
  }
}

Player::~Player() {}

std::string Player::getName(){
  return name;
}

void Player::setName(std::string name){
  this->name = name;
}

char Player::getSymbol(){
  return symbol;
} 

void Player::setSymbol(char symbol){
  this->symbol = symbol;
} 

int Player::getPlayerIndex(){
  return playerIndex;
}

void Player::setPlayerIndex(int playerIndex){
  this->playerIndex = playerIndex;
}

void Player::addMoney(int money){
  this->money += money;
} 

void Player::payBank(int money){
  this->money -= money;
}

void Player::payPlayer(int money, Player *player){
  this->money -= money;
  player->addMoney(money);
}

int Player::getMoney(){
  return money;
}

//adding property to player's properties
void Player::addProperty(Property *property){
  int pos = property->getPosition();
  properties[pos] = property;
  string propertyName = property->getName();
  if (propertyName == "AL" || propertyName == "ML") {
    arts1++;
  } else if (propertyName == "ECH" || propertyName == "PAS" || propertyName == "HH") {
    arts2++;
  } else if (propertyName == "RCH" || propertyName == "DWE" || propertyName == "CPH") {
    eng++;
  } else if (propertyName == "LHI" || propertyName == "BMH" || propertyName == "OPT") {
    health++;
  } else if (propertyName == "EV1" || propertyName == "EV2" || propertyName == "EV3") {
    env++;
  } else if (propertyName == "PHYS" || propertyName == "B1" || propertyName == "B2") {
    sci1++;
  } else if (propertyName == "EIT" || propertyName == "ESC" || propertyName == "C2") {
    sci2++;
  } else if (propertyName == "MC" || propertyName == "DC") {
    math++;
  }
}

//removing property from player's properties
void Player::removeProperty(Property *property){
  int pos = property->getPosition();
  properties[pos] = nullptr;
  string propertyName = property->getName();
  if (propertyName == "AL" || propertyName == "ML") {
    arts1--;
  } else if (propertyName == "ECH" || propertyName == "PAS" || propertyName == "HH") {
    arts2--;
  } else if (propertyName == "RCH" || propertyName == "DWE" || propertyName == "CPH") {
    eng--;
  } else if (propertyName == "LHI" || propertyName == "BMH" || propertyName == "OPT") {
    health--;
  } else if (propertyName == "EV1" || propertyName == "EV2" || propertyName == "EV3") {
    env--;
  } else if (propertyName == "PHYS" || propertyName == "B1" || propertyName == "B2") {
    sci1--;
  } else if (propertyName == "EIT" || propertyName == "ESC" || propertyName == "C2") {
    sci2--;
  } else if (propertyName == "MC" || propertyName == "DC") {
    math--;
  }
}

Property * Player::getProperty(){
  return *properties;
}

void Player::addResidence(){
  ++numResidence;
}

void Player::removeResidence(){
  --numResidence;
}

int Player::getResidence(){
  return numResidence;
} 

void Player::addGym(){
  ++numGym;
}

void Player::removeGym(){
  --numGym;
}

int Player::getGym(){
  return numGym;
}


void Player::setSquarePosition(int position){
  squarePosition = position;
} 

int Player::getSquarePosition(){
  return squarePosition;
}

//checks if player has the monopoly of the passed blocked
bool Player::hasMonopoly(string monopolyBlock){
  if (monopolyBlock == "Arts1") {
    if (arts1 == 2) return true;
  } else if (monopolyBlock == "Arts2") {
    if (arts2 == 3) return true;
  } else if (monopolyBlock == "Eng") {
    if (eng == 3) return true;
  } else if (monopolyBlock == "Health") {
    if (health == 3) return true;
  } else if (monopolyBlock == "Env") {
    if (env == 3) return true;
  } else if (monopolyBlock == "Sci1") {
    if (sci1 == 3) return true;
  } else if (monopolyBlock == "Sci2") {
    if (sci2 == 3) return true;
  } else if (monopolyBlock == "Math") {
    if (math == 2) return true;
  } 
  return false;
}

//when player is bankrupted and gives all assets to other player
void Player::BankruptOwePlayer(Player *giveto){
  giveto->addMoney(money);
  for (auto i:properties) {
    if (i != nullptr) {
      giveto->addProperty(i);
      char propertyType = i->propertyType();
      if(propertyType == 'R') {
        giveto->addResidence();
        removeResidence();
      } else if (propertyType == 'G'){
        giveto->addGym();
        removeGym();
      }
      removeProperty(i);
    }
  }

  for (int i = 0; i < numCups; ++i) {
    giveto->addCup();
  }
  money = 0;
  bankrupt = true;
  cout << getName() << " dropped out." << endl;
} 

//when player is bankrupted and returns all assets to bank
void Player::BankruptOweBank(){
  for (auto i:properties) {
    if (i != nullptr) {
      char propertyType = i->propertyType();
      if(propertyType == 'R') {
        removeResidence();
      } else if (propertyType == 'G'){
        removeGym();
      } 
      removeProperty(i);
    } 
  }
  money = -1;
  bankrupt = true;
  numCups = 0;
  cout << getName() << " dropped out." << endl;
}

bool Player::isBankrupt(){
  return bankrupt;
} 

void Player::setCup(int c){
  numCups = c;
}

int Player::getCup(){
  return numCups;
}

void Player::addCup(){
  ++numCups;
}

void Player::removeCup(){
  --numCups;
}  

bool Player::isAtTims(){
  return atTims;
}

void Player::setAtTims(bool state){
  atTims = state;
}

int Player::turnsAtTims(){
  return numTimsLine;
}

int Player::placeBid(int amount){
  bid = amount;
  return bid;
}

void Player::withdrawBid(){
  bid = 0;
}

int Player::getNumberDoubles(){
  return doubles;
}

void Player::changeNumberDouble(){
  if (doubles >= 3) {
    doubles = 0;
  } else {
    ++doubles;
  }
}

//calculates the player's net worth
int Player::netWorth() {
  int networth = money;
  for (auto i:properties) {
    if (i != nullptr) {
      string monoBlock = i->whichMonopolyBlock();
      networth += i->getPurchaseCost();
      int numImprovements = i->getImprovementCount(); 
      if (monoBlock == "arts1" || monoBlock == "arts2"){
        networth += (numImprovements * 50 );
      } else if (monoBlock == "eng" || monoBlock == "health"){
        networth += (numImprovements * 100); 
      } else if (monoBlock == "env" || monoBlock == "sci1"){
        networth += (numImprovements * 150); 
      } else if (monoBlock == "sci2" || monoBlock == "math"){
        networth += (numImprovements * 200); 
      }
    }
  }
  return networth;
}

int Player::mortgagedAssetsWorth() {
  int worth = 0;
  for (auto i:properties) {
    if (i != nullptr) {
      string monoBlock = i->whichMonopolyBlock();
      worth += (i->getPurchaseCost() / 2);
      int numImprovements = i->getImprovementCount(); 
      if (monoBlock == "arts1" || monoBlock == "arts2"){
        worth += (numImprovements * 25 );
      } else if (monoBlock == "eng" || monoBlock == "health"){
        worth += (numImprovements * 50); 
      } else if (monoBlock == "env" || monoBlock == "sci1"){
        worth += (numImprovements * 75); 
      } else if (monoBlock == "sci2" || monoBlock == "math"){
        worth += (numImprovements * 100); 
      }
    }
  }
  return worth;
}

void Player::trade(Player * player, Property * give, Property * receive){
  player->addProperty(give);
  addProperty(receive);
  player->removeProperty(receive);
  removeProperty(give);
}

void Player::trade(Player * player, int give, Property * receive){
  payPlayer(give, player);
  addProperty(receive);
  player->removeProperty(receive);

}

void Player::trade(Player * player, Property * give, int receive){
  removeProperty(give);
  player->addProperty(give);
  player->payPlayer(receive, this);

}

