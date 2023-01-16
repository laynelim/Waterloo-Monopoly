#include <string>
#include <iostream>
#include <iomanip>
#include "square.h"
#include "player.h"
using namespace std;

Square::Square(string name, int position) :  name{name}, position{position}{
  vector<Player> players;
  sumDice = 0;
}

Square::~Square(){}

string Square::getName(){
  return name;
}

vector<Player> Square::getPlayers(){
  return players;
}

void Square::addPlayer(Player * player){
  players.push_back(*player);
}

void Square::removePlayer(Player * player){
  for (size_t i = 0; i < players.size(); ++i) {
   if (players[i].getSymbol() == player->getSymbol()){
    players.erase(players.begin() + i);
   }
  }
}

int Square::getPosition(){
  return position;
}

void Square::printPlayers(){
  string toPrint = "";
  for (auto i:players) {
    bool isBankrupt = i.isBankrupt();
    if (isBankrupt == false) {
      toPrint += i.getSymbol();
    }
  }
  cout << left << setw(7) << toPrint;
}


int Square::getSumDice(){
  return sumDice;
}

void Square::setSumDice(int s){
  sumDice = s;
}

