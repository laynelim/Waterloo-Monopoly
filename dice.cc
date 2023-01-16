#include <cstdlib>
#include <ctime>
#include <iostream>
#include "dice.h"
using namespace std;

Dice::Dice(){
  dice1 = 0;
  dice2 = 0;
  isDouble = false;
} 

Dice::~Dice(){}

//roll 2 random die
void Dice::rollDice() { 
  isDouble = false;
  const int diceMin = 1;
  const int diceMax = 6;
  srand(time(NULL)); 
  dice1 = (rand() % diceMax) + diceMin;
  dice2 = (rand() % diceMax) + diceMin; 
  cout << "You have rolled " << dice1 << " and " << dice2 << endl;
  if (dice1 == dice2) isDouble = true;
}

bool Dice::doubleCheck() { 
  return isDouble; 
}

void Dice::setDouble(bool state) { 
  isDouble = state;
}

int Dice::getDice1() { 
  return dice1; 
} 

int Dice::getDice2(){ 
  return dice2; 
}

int Dice::getSum() { 
  return dice1 + dice2;
}

