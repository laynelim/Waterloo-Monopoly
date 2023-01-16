#include <iostream>
#include <fstream>
#include <string>
#include "gameplay.h"
#include "board.h"
using namespace std;

void usage(){
  cout << "Usage is any of:" << endl;
  cout << "./watopoly -load filename -testing" << endl;
  cout << "./watopoly -testing" << endl;
  cout << "./watopoly -load filename" << endl;
}

int main(int argc, char *argv[]) {
  Gameplay *g = new Gameplay();

  // program is called with arguments
  if (argc == 4){
    if ((string(argv[1]) == "-load") && (string(argv[3]) == "-testing")) { 
      g->setTest();
      g->loadGame(string(argv[2]));
      g->playGame();
    } else {
      usage();
    }
  } else if ((argc == 2) || (argc == 3)){
    if (string(argv[1]) == "-load"){
      g->loadGame(string(argv[2]));
      g->playGame();
    } else if (string(argv[1]) == "-testing"){
      g->setTest(); //sets the test bool to true; 
      g->newGame();
      g->playGame();
    } else {
      usage();
    }
  } else if (argc == 1){
    g->newGame();
    g->playGame();
  } else {
    usage();
  }
  
  return 0;
}

