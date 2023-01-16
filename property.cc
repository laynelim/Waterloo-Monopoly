#include <string>
#include <iomanip>
#include "property.h"
#include "square.h"
#include "player.h"
using namespace std;

Property::Property(string name, int position, int purchaseCost) : Square{name, position}, purchaseCost{purchaseCost}{
  owner = nullptr;
  improvementCount = 0;
  mortgaged = false;
}

Property::~Property(){
  
}

void Property::setOwner(Player * player){
  owner = player;
}

Player * Property::getOwner(){
  return owner;
}

int Property::getPurchaseCost(){
  return purchaseCost;
}

bool operator== (Property& p1, Property& p2){
  return (p1.getName() == p2.getName());
}

char Property::propertyType(){
  if (getName() == "PAC" || getName() == "CIF"){
    return 'G';
  } else if (getName() == "MKV" || getName() == "V1" || getName() == "UWP" || getName() == "REV"){
    return 'R';
  } else {
    return 'A';
  }
}

void Property::incImprovementCount(){
  improvementCount = improvementCount + 1;
}

void Property::decImprovementCount(){
  improvementCount = improvementCount - 1;
}

int Property::getImprovementCount(){
  return improvementCount;
}

void Property::setImprovementCount(int count){
  improvementCount = count;
}

void Property::printImprovements() {
  string toPrint = "";
  for(int i = 0; i < getImprovementCount(); ++i) {
    toPrint += "I";
  }
  cout << left << setw(7) << toPrint;
}

//COME BACK LATER
void Property::mortgage(){
  
}

void Property::unmortgage(){
  
}

bool Property::isMortgaged(){
  return mortgaged; 
}

void Property::setMortgaged(bool state){
  mortgaged = state;
}

void Property::auction(){
  
}

string Property::whichMonopolyBlock() {
  string propertyName = getName();
  if (propertyName == "AL" || propertyName == "ML") {
    return "arts1";
  } else if (propertyName == "ECH" || propertyName == "PAS" || propertyName == "HH") {
    return "arts2";
  } else if (propertyName == "RCH" || propertyName == "DWE" || propertyName == "CPH") {
    return "eng";
  } else if (propertyName == "LHI" || propertyName == "BMH" || propertyName == "OPT") {
    return "health";
  } else if (propertyName == "EV1" || propertyName == "EV2" || propertyName == "EV3") {
    return "env";
  } else if (propertyName == "PHYS" || propertyName == "B1" || propertyName == "B2") {
    return "sci1";
  } else if (propertyName == "EIT" || propertyName == "ESC" || propertyName == "C2") {
    return "sci2";
  } else if (propertyName == "MC" || propertyName == "DC") {
    return "math";
  } else {
    return "";
  }
}





