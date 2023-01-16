#include <iostream> 
#include <fstream>
#include <sstream>
#include <string>
#include "player.h"
#include "gameplay.h"
#include "square.h"
#include "board.h"
using namespace std;

Gameplay::Gameplay(){
  b = new Board;
}

Gameplay::~Gameplay(){
  delete b;
}

void Gameplay::newGame(){
  b->newGame();
}

//command interpreter
void Gameplay::playGame() { 
  while (!(b->gameOver())) { 
    cout << endl;
    cout << "What is your next decision?" << endl; 
    cout << "Enter 'help' to see a list of commands" << endl; 
    string input;
    cin >> input; 

    if (cin.eof()) {
      break;
    }

    if (input == "roll") { 
      cout << endl;
      if (b->gethasRolled()) { 
        cout << "You've already rolled this turn!" << endl; 
        continue; 
      } else if (test) {
        string input;
        getline(cin, input);
        if (input == "") {
          b->roll(); 
        } else {
          istringstream in{input};
          int die1, die2;
          in >> die1;
          in >> die2;
          if ((0 <= die1)  && (0 <= die2)) {
            b->roll(die1, die2);
          } 
        } 
      } else {
        b->roll();
      }
    } else if (input == "next"){
      cout << endl;
      if (b->gethasRolled()){
        b->next();
      } else {
        cout << "You cannot skip your turn. You need to roll!" << endl;
      }
      

    } else if (input == "help"){
      cout << endl;
      cout << "'roll' : This command is to roll the dice, if you are allowed to roll" << endl;
      cout << "'next' : This command gives control to the next player" << endl;
      cout << "'assets' : This command is to show the assets of the current player" << endl;
      cout << "'all' : This command is to show the assets of all the players" << endl;
      cout << "'save' : This command is to save your current game. You will then be prompted to enter a file name" << endl;
      cout << "'end' : This command is to end the game without saving any progress" << endl;


    } else if (input == "save"){
      cout << endl;
      cout << "Please enter a file name to save your game progress:" << endl;
      string savefile;
      cin >> savefile;
      saveGame(savefile);
      cout << "Game ended. Progress has been saved." << endl;
      break;

    } else if (input == "end") {
      cout << endl;
      cout << "Game ended. Progress not saved." << endl;
      break;
      
    } else if (input == "assets") { 
      cout << endl;
      b->assets();
      
    } else if (input == "all") {
      cout << endl;
      b->all();

    } else {
      cout << endl;
      cout << "Invalid command" << endl;
    }
  }
}

void Gameplay::saveGame(string saveFile){
  b->saveGame(saveFile);
}

void Gameplay::loadGame(string loadedFile){
  b->loadGame(loadedFile);
}

void Gameplay::setTest() { 
  test = true;
}
