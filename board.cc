#include "board.h"
#include "dice.h"
#include "player.h"
#include "square.h"
#include "property.h"
#include "nonProperty.h"
#include "academic.h"
#include "gym.h"
#include "residence.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream> 
#include <iomanip>
using namespace std; 

Board::Board(){
    totalCups = 0;
    hasRolled = false;
    gameEnded = false;
    numOfPlayers = 0;
    for (int i = 0; i < 6; ++i){
        players[i] = nullptr;
    }
    curPlayer = players[0];
    dice = new Dice();
    
    board[0] = new collectOsap("COLLECT OSAP", 0);
    board[1] = new Academic("AL", 1, 40, "Arts1", 50, 2, 10, 30 , 90 , 160, 250);
    board[2] = new slc("SLC", 2);
    board[3] = new Academic("ML", 3, 60, "Arts1", 50, 4, 20, 60, 180, 320, 450);
    board[4] = new tuition("TUITION", 4);
    board[5] = new Residence("MKV", 5, 200);
    board[6] = new Academic("ECH", 6, 100, "Arts2", 50, 6, 30, 90, 270, 400, 550);
    board[7] = new nh("NEEDLES HALL", 7);
    board[8] = new Academic("PAS", 8, 100, "Arts2", 50, 6, 30, 90, 270, 400, 550);
    board[9] = new Academic("HH", 9, 120, "Arts2", 50, 8, 40, 100, 300, 450, 600);
    board[10] = new timsLine("DC Tims Line", 10);
    board[11] = new Academic("RCH", 11, 140, "Eng", 100, 10, 50, 150, 450, 625, 750);
    board[12] = new Gym("PAC", 12, 150);
    board[13] = new Academic("DWE", 13, 140, "Eng", 100, 10, 50, 150, 450, 625, 750);
    board[14] = new Academic("CPH", 14, 160, "Eng", 100, 12, 60, 180, 500, 700, 900);
    board[15] = new Residence("UWP", 15, 200);
    board[16] = new Academic("LHI", 16, 180, "Health", 100, 14, 70, 200, 550, 750, 950);
    board[17] = new slc("SLC", 17);
    board[18] = new Academic("BMH", 18, 180, "Health", 100, 14, 70, 200, 550, 750, 950);
    board[19] = new Academic("OPT", 19, 200, "Health", 100, 16, 80, 220, 600, 800, 1000);
    board[20] = new gooseNesting("Goose Nesting", 20);
    board[21] = new Academic("EV1", 21, 220, "Env", 150, 18, 90, 250, 700, 875, 1050);
    board[22] = new nh("NEEDLES HALL", 22);
    board[23] = new Academic("EV2", 23, 220, "Env", 150, 18, 90, 250, 700, 875, 1050);
    board[24] = new Academic("EV3", 24, 240, "Env", 150, 20, 100, 300, 750, 925, 1100);
    board[25] = new Residence("V1", 25, 200);
    board[26] = new Academic("PHYS", 26, 260, "Sci1", 150, 22, 110, 330, 800, 975, 1150);
    board[27] = new Academic("B1", 27, 260, "Sci1", 150, 22, 110, 330, 800, 975, 1150);
    board[28] = new Gym("CIF", 28, 150);
    board[29] = new Academic("B2", 29, 280, "Sci1", 150, 24, 120, 360, 850, 1025, 1200);
    board[30] = new gotoTims("GO TO TIMS", 30);
    board[31] = new Academic("EIT", 31, 300, "Sci2", 200, 26, 130, 390, 900, 1100, 1275);
    board[32] = new Academic("ESC", 32, 300, "Sci2", 200, 26, 130, 390, 900, 1100, 1275);
    board[33] = new slc("SLC", 33);
    board[34] = new Academic("C2", 34, 320, "Sci2", 200, 28, 150, 450, 1000, 1200, 1400);
    board[35] = new Residence("REV", 35, 200);
    board[36] = new nh("NEEDLES HALL", 36);
    board[37] = new Academic("MC", 37, 350, "Math", 200, 35, 175, 500, 1100, 1300, 1500);
    board[38] = new coop("COOP FEE", 38);
    board[39] = new Academic("DC", 39, 400, "Math", 200, 50, 200, 600, 1400, 1700, 2000);
}

Board::~Board(){
    for (int i = 0; i < 40; ++i) {
        delete board[i];
    }
    for (int j = 0; j < 6; ++j) {
        delete players[j];
    }
    delete curPlayer;
    delete dice;
}

//initializes a new game
void Board::newGame(){
    cout << "Enter the number of players (min 2, max 6):" << endl;
    int numPlayers;
    while (cin >> numPlayers){
        if ((numPlayers < 2) || (numPlayers > 6)){
            cout << "Invalid number of players. Enter the number of players (min 2, max 6):" << endl;
        } else {
            break;
        }
    }
    this->numOfPlayers = numPlayers;

    string playerName;
    for (int i = 1; i <= numPlayers; ++i){
        cout << "Player " << i << " , please enter your name:" << endl;
        while (cin >> playerName){
            if (playerName == "BANK"){
                cout << "Invalid name. Enter your name again:" << endl;
                continue;
            }

            bool taken = false;
            for (int j = 1; j < i; ++j){
                if (players[j - 1]->getName() == playerName){
                    cout << "This name is already taken. Enter your name again:" << endl;
                    taken = true;
                    break;
                }
            }
            if (taken){
              continue;
            } else {
              break;
            }        
        }

        char symbol;
        string piece;
        cout << "Players choose from the following pieces to represent them on the board:" << endl;
        cout << "G (Goose) | B (GRT Bus) | D (Tim Hortons Doughnut) | P (Professor) | S (Student) | $ (Money) | L (Laptop) | T (Pink tie) | " << endl;
        cout << playerName << ", please choose your piece:" << endl;
        while (cin >> piece){
            if (!((piece == "G") || (piece == "B") || (piece == "D") || (piece == "P") || 
            (piece == "S") || (piece == "$") || (piece == "L") || (piece == "T"))){
                cout << "Invalid piece chosen. Enter your piece again:" << endl;
                continue;
            }
            
            istringstream ss{piece};
            ss >> symbol;
            bool taken = false;
            for (int k = 1; k < i; ++k){
                if (players[k - 1]->getSymbol() == symbol){
                    cout << "This piece is already taken. Enter your piece again:" << endl;
                    taken = true;
                    break;
                }
            }
            if (taken){
              continue;
            } else {
              break;
            } 
        }
        
        players[i - 1] = new Player(playerName, symbol, 1500, 0, i - 1, 0);
        board[0]->addPlayer(players[i - 1]);
    }    
    cout << "Starting the game...." << endl; 
    displayBoard();
    cout << endl;
    curPlayer = players[0];
    cout << curPlayer->getName() << "'s turn!" << endl;
}



int Board::getCups(){
    int cups = 0;
    for(auto i:players) {
        if (i != nullptr) {
            cups += i->getCup();
        }
    }
    return cups;
} 

//rolling dicd in testing mode
void Board::roll(int dice1, int dice2) { 
    int numofRolls = 1; 
    while ((dice1 == dice2) && numofRolls < 3) {   
        cout << "You've rolled a double, and you must roll again" << endl;
        cout << "Please enter 'roll <dice1> <dice2>' " << endl;
        string input;
        while (true) {
            cin >> input;
            if (input == "roll") {
                break;
            } else {
                cout << "Wrong command!" << endl;
                cout << "Please enter 'roll' to roll again" << endl;  
            }
        }
        cin >> dice1;
        cin >> dice2;
        numofRolls++;
    }
    int curPos = curPlayer->getSquarePosition();
    int nextPos = curPos;
    int diceSum = dice1 + dice2; 
    bool passedOSAP = false;
    if (numofRolls == 3 && (dice1 != dice2)) { 
        cout << "You've rolled a double 3 times, it's time to go to the Tims line!" << endl;
        getSquare(curPos)->removePlayer(curPlayer);
        curPlayer->setSquarePosition(10);
        getSquare(10)->addPlayer(curPlayer);

        displayBoard();
        cout << endl;
        getSquare(10)->squareAction(curPlayer); 
        
             
    } else { //the case where we move the player normally 
        if ((curPos + diceSum) < 40){
            nextPos = curPos + diceSum;
        } else if ((curPos + diceSum) == 40) {
            nextPos = 0;
        } else {
            passedOSAP = true;
            nextPos = curPos + diceSum - 40;
        }
        curPlayer->setSquarePosition(nextPos);
        getSquare(curPos)->removePlayer(curPlayer);
        getSquare(nextPos)->addPlayer(curPlayer);
        

        displayBoard();
        cout << endl;

        if (passedOSAP){
            getSquare(0)->squareAction(curPlayer);  
        }
        if ((nextPos == 12) || (nextPos == 28)){
            getSquare(nextPos)->setSumDice(diceSum);
        }
        getSquare(nextPos)->squareAction(curPlayer);  
    }
    hasRolled = true;
    gameContinue();
}

//rolling dice randomly
void Board::roll() { 
    int numofRolls = 1; 
    dice->rollDice(); 
    while (dice->doubleCheck() && numofRolls < 3) {   
        
        cout << "You've rolled a double, and you must roll again" << endl;
        cout << "Please enter 'roll' to roll again" << endl;

        string input;
        while (true) {
            cin >> input;
            if (input == "roll") {
                break;
            } else {
                cout << "Wrong command!" << endl;
                cout << "Please enter 'roll' to roll again" << endl;  
            }
        }
        dice->rollDice(); //immediately rolling again for the player
        numofRolls++;
    }
    int curPos = curPlayer->getSquarePosition();
    int nextPos = curPos;
    int diceSum = dice->getSum(); 
    bool passedOSAP = false;
    if (numofRolls == 3 && dice->doubleCheck()) { 
        cout << "You've rolled a double 3 times, it's time to go to the Tims line!" << endl;
        getSquare(curPos)->removePlayer(curPlayer);
        curPlayer->setSquarePosition(10);
        getSquare(10)->addPlayer(curPlayer);

        displayBoard();
        cout << endl;
        getSquare(10)->squareAction(curPlayer); 
        
             
    } else { //the case where we move the player normally 
        if ((curPos + diceSum) < 40){
            nextPos = curPos + diceSum;
        } else if ((curPos + diceSum) == 40) {
            nextPos = 0;
        } else {
            passedOSAP = true;
            nextPos = curPos + diceSum - 40;
        }
        curPlayer->setSquarePosition(nextPos);
        getSquare(curPos)->removePlayer(curPlayer);
        getSquare(nextPos)->addPlayer(curPlayer);
        

        displayBoard();
        cout << endl;

        if (passedOSAP){
            getSquare(0)->squareAction(curPlayer);  
        }
        if ((nextPos == 12) || (nextPos == 28)){
            getSquare(nextPos)->setSumDice(diceSum);
        }
        getSquare(nextPos)->squareAction(curPlayer);  
    }

    hasRolled = true;
    gameContinue();
}

//give control to next player
void Board::next() {
    int nextPerson = curPlayer->getPlayerIndex(); 

    if (nextPerson < (numOfPlayers - 1)){
      curPlayer = players[nextPerson + 1];
    }
    if (nextPerson == (numOfPlayers - 1)){
      curPlayer = players[0];
    }
    nextPerson = curPlayer->getPlayerIndex(); 

    while (curPlayer->isBankrupt()){
      if (nextPerson < (numOfPlayers - 1)){
        curPlayer = players[nextPerson + 1];
      }
      if (nextPerson == (numOfPlayers - 1)){
        curPlayer = players[0];
      }
      nextPerson = curPlayer->getPlayerIndex(); 
    }
  
    cout << curPlayer->getName() << "'s turn!" << endl;
    hasRolled = false;  
}

//loading a game
void Board::loadGame(string loadedFile){
    ifstream file;
    string name; 
    char symbol; 
    int cash; 
    int pos;
    string propertyName; 
    string owner; 
    int improvements; 
    
    int numCups;
    
    file.open(loadedFile);
    file >> numOfPlayers; 

    //setting the players 
    for (int i = 0; i < numOfPlayers; i++) {
        file >> name; 
        file >> symbol; 
        file >> numCups;
        file >> cash; 
        file >> pos; 
        //implement if a player is in timsline here 
           
        players[i] = new Player(name, symbol, cash, pos, i, numCups);
        board[pos]->addPlayer(players[i]);
    }
    curPlayer = players[0];  //current player is first player in the file

    //reading in properties and their owners
    for (int i = 0; i < 40; i++){ 
        switch(i){
            case 0: case 2: case 4: case 7: case 10: case 17: case 20: case 22: case 30: case 33: case 36: case 38:
                continue;
        }
        file >> propertyName;
        file >> owner; 
        file >> improvements;
        
        if (owner == "BANK") {  // if the owner is a bank we don't do anything
            continue; 
        } else { 
            Property *tmp = dynamic_cast<Property *> (board[i]);
            for (int k = 0; k < numOfPlayers; ++k){
                if (owner == players[k]->getName()){                 
                    tmp->setOwner(players[k]);
                    tmp->setImprovementCount(improvements);
                    players[k]->addProperty(tmp);

                    switch(i){
                        case 12: case 28:
                            players[k]->addGym();
                            break;
                        case 5: case 15: case 25: case 35:
                            players[k]->addResidence();
                            break;
                    }
                }
            }
            

        }
    }

    displayBoard();
    cout << endl;
    cout << curPlayer->getName() << "'s turn!" << endl;
   
}


//saving a game
void Board::saveGame(string saveFile){
    ofstream sfile;
    sfile.open(saveFile);
  
    //save number of players
    sfile << this->numOfPlayers << endl;
  
    //save players info
    for (int i = 0; i < numOfPlayers; ++i){
        sfile << players[i]->getName() << " " << players[i]->getSymbol() << " " << players[i]->getCup() << " " << players[i]->getMoney() << " " << players[i]->getSquarePosition() << endl;
    }
  
    //save properties info
    string o = "";
    for (int j = 0; j < 40; ++j){
        switch(j){
            case 0: case 2: case 4: case 7: case 10: case 17: case 20: case 22: case 30: case 33: case 36: case 38:
                continue;
        }
        Property *tmp = dynamic_cast<Property *> (board[j]);
        if (!(tmp->getOwner())) {
            o = "BANK";
        } else {
             o = tmp->getOwner()->getName();
        }
        sfile << tmp->getName() << " " << o << " " << tmp->getImprovementCount() << endl;
    }
        sfile.close();
}

bool Board::gethasRolled() { 
    return hasRolled;
}


Square* Board::getSquare(int pos) { 
    return board[pos];
}

//display assets of current player
void Board::assets(){
    cout << "The total assets of " << curPlayer->getName() << " are:" << endl;
    cout << "Total money: $" << curPlayer->getMoney() << endl;
    cout << "Your properties are: "; 

    for (int j = 0; j < 40; ++j){
        switch(j){
            case 0: case 2: case 4: case 7: case 10: case 17: case 20: case 22: case 30: case 33: case 36: case 38:
                continue;
        }
        Property *tmp = dynamic_cast<Property *> (board[j]);
        if (tmp->getOwner() != nullptr) {
            if ((tmp->getOwner()->getName()) == curPlayer->getName()){
                cout << tmp->getName() << " ";
            }
        }
    }
    cout << endl;

}

//display assets of all players
void Board::all(){   
    for (int i = 0; i < numOfPlayers; ++i){
        cout << "The total assets of " << players[i]->getName() << " are:" << endl;
        cout << "Total money: $" << players[i]->getMoney() << endl;
        cout << "Your properties are: "; 

        for (int j = 0; j < 40; ++j){
            switch(j){
                case 0: case 2: case 4: case 7: case 10: case 17: case 20: case 22: case 30: case 33: case 36: case 38:
                    continue;
            }
            Property *tmp = dynamic_cast<Property *> (board[j]);
            if (tmp->getOwner() != nullptr) {
                if ((tmp->getOwner()->getName()) == players[i]->getName()){
                    cout << tmp->getName() << " ";
                }
            }
        }

        cout << endl << endl;
    }
}



bool Board::gameOver() { 
    return gameEnded;
}

//checks if only 1 player is left-> condition to end game
void Board::gameContinue() {
  int playersleft = 0;
  int index = 0;
  for (int i = 0; i < numOfPlayers; ++i){
    if (!(players[i]->isBankrupt())){
      playersleft = playersleft + 1;
      index = i;
    }
  }
  if (playersleft == 1){
    cout << endl << "Congratulations " << players[index]->getName() << "! You are the only one who has not dropped out of university!" << endl;
    cout << "You have successfully monopolized Waterloo!" << endl;  
    cout << "Game ended :)" << endl;
    gameEnded = true;
  } else {
    gameEnded = false;
  }

}

void Board::improvementSell(Property * property){
    int pos = property->getPosition();
    if (board[pos]->getName() == property->getName()) {
            property->decImprovementCount();          
    }
} 

void Board::propertySell(Property * property){
 /*   int pos = property->getPosition();
    if (board[pos]->getName() == property->getName()) {
            property->();          
    } */
}

void Board::propertyImprove(Property * property){
    int pos = property->getPosition();
    if (board[pos]->getName() == property->getName()) {
        property->incImprovementCount();
        
    }
}



// Helper for displayBoard
void printBottom(){
    cout << left << setw(8) << "|_______" ;
    cout << left << setw(72) << "|" ;
    cout << left << setw(8) << "|_______|" << endl;
}


void Board::displayBoard(){
    Property *tmp = dynamic_cast<Property *> (board[1]);

    //1
    for (int i = 0; i < 89; ++i) {
    	cout << "_";
    }
    cout << endl;
    
    //2
    for(int i = 20; i <= 30; i++) {
        if (i == 20) {
            cout << left << setw(8) << "|Goose";
        } else if (i == 22) {
            cout << left << setw(8) << "|NEEDLES";
        } else if (i == 25) {
            cout << left << setw(8) << "|V1";
        } else if (i == 28) {
            cout << left << setw(8) << "|CIF";
        } else if (i == 30) {
            cout << left << setw(8) << "|GO TO";
            cout << "|" << endl;
        } else {
            cout << "|";
            tmp = dynamic_cast<Property *> (board[i]);
            tmp->printImprovements();
        }
    }

    //3
    for(int i = 20; i <= 30; i++) {
        if (i == 20) {
            cout << left << setw(8) << "|Nesting";
        } else if (i == 22) {
            cout << left << setw(8) << "|HALL";
        } else if (i == 25 || i == 28) {
            cout << left << setw(8) << "|";
        } else if (i == 30) {
            cout << left << setw(8) << "|Tims";
            cout << "|" << endl;
        } else {
            cout << "|-------";
        }
    }

    //4
    for(int i = 20; i <= 30; i++) {
        if (i == 20 || i == 22 || i == 25 || i == 28) {
            cout << left << setw(8) << "|";
        } else if (i == 30) {
            cout << left << setw(8) << "|";
            cout << "|" << endl;
        } else {
            cout << left << "|" << setw(7) << board[i]->getName();
        }
    }

    //5 
    for(int i = 20; i <= 30; i++) {
        cout << "|";
        board[i]->printPlayers();
        if (i == 30) {
            cout << "|" << endl;
        }
    }
    //6
    for(int i = 20; i <= 30; i++) {
        if (i == 30) {
            cout << left << setw(8) << "|_______";
            cout << "|" << endl;
        } else {
            cout << left << setw(8) << "|_______";
        }
    }
    //7
    cout << "|";
    tmp = dynamic_cast<Property *> (board[19]);
    tmp->printImprovements();
    cout << left << setw(72) << "|" ;
    cout << "|";
    tmp = dynamic_cast<Property *> (board[31]);
    tmp->printImprovements();    cout << "|" << endl;

    //8
    cout << left << setw(8) << "|-------" ;
    cout << left << setw(72) << "|" ;
    cout << left << setw(8) << "|-------|" << endl;

    //9
    cout << left << "|" << setw(7) << board[19]->getName();
    cout << left << setw(72) << "|" ;
    cout << left << "|" << setw(7) << board[31]->getName();
    cout << "|" << endl;

    //10
    cout << "|";
    board[19]->printPlayers();
    cout << left << setw(72) << "|" ;
    cout << "|";
    board[31]->printPlayers();
    cout << "|" << endl;
    
    //11
    printBottom();

    //12
    cout << "|";
    tmp = dynamic_cast<Property *> (board[18]);
    tmp->printImprovements();
    cout << left << setw(72) << "|" ;
    cout << "|";
    tmp = dynamic_cast<Property *> (board[32]);
    tmp->printImprovements();
    cout << "|" << endl;

    //13
    cout << left << setw(8) << "|-------" ;
    cout << left << setw(72) << "|" ;
    cout << left << setw(8) << "|-------|" << endl;

    //14
    cout << left << "|" << setw(7) << board[18]->getName();
    cout << left << setw(72) << "|" ;
    cout << left << "|" << setw(7) << board[32]->getName();
    cout << "|" << endl;

    //15
    cout << "|";
    board[18]->printPlayers();
    cout << left << setw(72) << "|" ;
    cout << "|";
    board[32]->printPlayers();
    cout << "|" << endl;
    
    //16
    printBottom();

    //17
    cout << left << "|" << setw(7) << board[17]->getName();
    cout << left << setw(72) << "|" ;
    cout << left << "|" << setw(7) << board[33]->getName();
    cout << "|" << endl;

    //18 
    cout << left << setw(8) << "|";
    cout << left << setw(72) << "|" ;
    cout << left << setw(8) << "|";
    cout << "|" << endl;
    
    //19
    cout << left << setw(8) << "|";
    cout << left << setw(72) << "|" ;
    cout << left << setw(8) << "|";
    cout << "|" << endl;
    
    //20 
    cout << "|";
    board[17]->printPlayers();
    cout << left << setw(72) << "|" ;
    cout << "|";
    board[33]->printPlayers();
    cout << "|" << endl;
    
    //21
    printBottom();

    //22
    cout << "|";
    tmp = dynamic_cast<Property *> (board[16]);
    tmp->printImprovements();
    cout << left << setw(72) << "|" ;
    cout << "|";
    tmp = dynamic_cast<Property *> (board[34]);
    tmp->printImprovements();
    cout << "|" << endl;

    //23
    cout << left << setw(8) << "|-------" ;
    cout << left << setw(72) << "|" ;
    cout << left << setw(8) << "|-------|" << endl;

    //24
    cout << left << "|" << setw(7) << board[16]->getName();
    cout << left << setw(72) << "|" ;
    cout << left << "|" << setw(7) << board[34]->getName();
    cout << "|" << endl;

    //25
    cout << "|";
    board[16]->printPlayers();
    cout << left << setw(14) << "|" ;
    cout << left << "____________________________________________";
    cout << left << setw(14) << "_";
    cout << "|";
    board[34]->printPlayers();
    cout << "|" << endl;

    //26
    cout << left << setw(8) << "|_______" ;
    cout << left << setw(13) << "|" ;
    cout << left << setw(46) << "|";
    cout << left << setw(13) << "|" ;
    cout << left << setw(9) << "|_______|" << endl;

    //27
    cout << left << "|" << setw(7) << board[15]->getName();
    cout << left << setw(13) << "|" ;
    cout << left << "| #   #  ##  #####  ###  ###   ###  #   #   # ";
    cout << left << setw(13) << "|" ;
    cout << left << "|" << setw(7) << board[35]->getName();
    cout << "|" << endl;
    
    //28
    cout << left << setw(8) << "|";
    cout << left << setw(13) << "|" ;
    cout << left << "| #   # #  #   #   #   # #  # #   # #   #   # ";
    cout << left << setw(13) << "|" ;
    cout << left << setw(8) << "|";
    cout << "|" << endl;

    //29
    cout << left << setw(8) << "|";
    cout << left << setw(13) << "|" ;
    cout << left << "| # # # ####   #   #   # ###  #   # #    # #  ";
    cout << left << setw(13) << "|" ;
    cout << left << setw(8) << "|";
    cout << "|" << endl;

    //30
    
    cout << "|";
    board[15]->printPlayers();
    cout << left << setw(13) << "|" ;
    cout << left << "| # # # #  #   #   #   # #    #   # #     #   ";
    cout << left << setw(13) << "|" ;
    cout << "|";
    board[25]->printPlayers();
    cout << "|" << endl;

    //31
    cout << left << setw(8) << "|_______" ;
    cout << left << setw(13) << "|" ;
    cout << left << "| ##### #  #   #    ###  #     ###  ####  #   ";
    cout << left << setw(13) << "|" ;
    cout << left << setw(9) << "|_______|" << endl;

    //32
    cout << "|";
    tmp = dynamic_cast<Property *> (board[14]);
    tmp->printImprovements();
    cout << left << setw(13) << "|" ;
    cout << left << "|_____________________________________________";
    cout << left << setw(13) << "|";
    cout << left << setw(9) << "|NEEDLES|" << endl;
    
    //33
    cout << left << setw(8) << "|-------" ;
    cout << left << setw(72) << "|" ;
    cout << left << setw(8) << "|HALL";
    cout << "|" << endl;

    //34 
    cout << left << "|" << setw(7) << board[14]->getName();
    cout << left << setw(72) << "|" ;
    cout << left << setw(8) << "|";
    cout << "|" << endl;

    //35
    cout << "|";
    board[14]->printPlayers();
    cout << left << setw(72) << "|" ;
    cout << "|";
    board[36]->printPlayers();
    cout << "|" << endl;

    //36
    printBottom();

    //37
    cout << "|";
    tmp = dynamic_cast<Property *> (board[13]);
    tmp->printImprovements();
    cout << left << setw(72) << "|" ;
    cout << "|";
    tmp = dynamic_cast<Property *> (board[37]);
    tmp->printImprovements();
    cout << "|" << endl;

    //38
    cout << left << setw(8) << "|-------" ;
    cout << left << setw(72) << "|" ;
    cout << left << setw(8) << "|-------|" << endl;

    //39
    cout << left << "|" << setw(7) << board[13]->getName();
    cout << left << setw(72) << "|" ;
    cout << left << "|" << setw(7) << board[37]->getName();
    cout << "|" << endl;

    //40
    cout << "|";
    board[13]->printPlayers();
    cout << left << setw(72) << "|" ;
    cout << "|";
    board[37]->printPlayers();
    cout << "|" << endl;
    
    //41
    printBottom();
    
    //42
    cout << left << "|" << setw(7) << board[12]->getName();
    cout << left << setw(72) << "|" ;
    cout << left << "|" << setw(7) << "COOP";
    cout << "|" << endl;

    //43
    cout << left << setw(8) << "|";
    cout << left << setw(72) << "|" ;
    cout << left << "|" << setw(7) << "FEE" ;
    cout << "|" << endl;
    
    //44
    cout << left << setw(8) << "|";
    cout << left << setw(72) << "|" ;
    cout << left << setw(8) << "|";
    cout << "|" << endl;
    
    //45
    cout << "|";
    board[12]->printPlayers();
    cout << left << setw(72) << "|" ;
    cout << "|";
    board[38]->printPlayers();
    cout << "|" << endl;
    
    //46
    printBottom();

    //47
    cout << "|";
    tmp = dynamic_cast<Property *> (board[11]);
    tmp->printImprovements();
    cout << left << setw(72) << "|" ;
    cout << "|";
    tmp = dynamic_cast<Property *> (board[39]);
    tmp->printImprovements();
    cout << "|" << endl;

    //48
    cout << left << setw(8) << "|-------" ;
    cout << left << setw(72) << "|" ;
    cout << left << setw(8) << "|-------|" << endl;

    //49
    cout << left << "|" << setw(7) << board[11]->getName();
    cout << left << setw(72) << "|" ;
    cout << left << "|" << setw(7) << board[39]->getName();
    cout << "|" << endl;

    //50
    cout << "|";
    board[11]->printPlayers();
    cout << left << setw(72) << "|" ;
    cout << "|";
    board[39]->printPlayers();
    cout << "|" << endl;

    //51
    cout << left << setw(8) << "|_______" ;
    cout << left << setw(72) << "|_______________________________________________________________________" ;
    cout << left << setw(8) << "|_______" ;
    cout << "|" << endl;
    
    //52
    for(int i = 10; i >= 0; i--) {
        if (i == 10) {
            cout << left << setw(8) << "|DC Tims";
        } else if (i == 7) {
            cout << left << setw(8) << "|NEEDLES";
        } else if (i == 5 || i == 4 || i == 2) {
            cout << left << "|" << setw(7) << board[i]->getName();
        } else if (i == 0) {
            cout << left << setw(8) << "|COLLECT";
            cout << "|" << endl;
        } else {
            cout << "|";
            tmp = dynamic_cast<Property *> (board[i]);
            tmp->printImprovements();
        }
    }

    //53
    for(int i = 10; i >= 0; i--) {
        if (i == 10) {
            cout << left << setw(8) << "|Line";
        } else if (i == 7) {
            cout << left << setw(8) << "|HALL";
        } else if (i == 5 || i == 4 || i == 2) {
            cout << left << setw(8) << "|" ;
        } else if (i == 0) {
            cout << left << setw(8) << "|OSAP";
            cout << "|" << endl;
        } else {
            cout << left << setw(8) << "|-------" ;
        }
    }
    
    //54
    for(int i = 10; i >= 0; i--) {
        if (i == 9 || i == 8 || i == 6 || i == 3 || i == 1) {
            cout << left << "|" << setw(7) << board[i]->getName();
        } else if (i == 0){
            cout << left << setw(8) << "|";
            cout << "|" << endl;
        } else {
            cout << left << setw(8) << "|" ;
        }
    }

    //55
    for(int i = 10; i >= 0; i--) {
        cout << "|";
        board[i]->printPlayers();
        if (i == 0){
            cout << "|" << endl;
        }
    }

    //56  
    for(int i = 10; i >= 0; i--) {
        if (i == 0){
            cout << left << setw(8) << "|_______" ;
            cout << "|" << endl;
        } else {
            cout << left << setw(8) << "|_______" ;
        }
    }
    
} 

