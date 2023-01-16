#include <iostream>
#include <string>
#include "nonProperty.h"
#include "player.h"
using namespace std;

nonProperty::nonProperty(string name, int position) : 
Square{name, position} {} 

nonProperty::~nonProperty() {}

collectOsap::collectOsap(string name, int position) :
nonProperty{name, position} {} 

collectOsap::~collectOsap() {} 

//action when player lands on OSAP
void collectOsap::squareAction(Player * p) { 
    cout << "You collect $200 in OSAP" << endl;
    p->addMoney(200);
}

timsLine::timsLine(string name, int position) : 
nonProperty{name, position} {} 

timsLine::~timsLine() {} 

//action when player lands on Tims Line - nothing
void timsLine::squareAction(Player * p) {
    cout << "You are at the Tims Line" << endl;
}

gotoTims::gotoTims(string name, int position) : 
nonProperty{name, position} {} 

gotoTims::~gotoTims() {} 

//action when player lands on Goto Tims Line
void gotoTims::squareAction(Player * p) {
    cout << "You go to Tims Line" << endl;
    p->setAtTims(true);
    p->setSquarePosition(10); 
}


gooseNesting::gooseNesting(string name, int position) : 
nonProperty{name, position} {}

gooseNesting::~gooseNesting() {}

//action when player lands on Goose Nesting - nothing
void gooseNesting::squareAction(Player * p) { 
    cout << "You are attacked by a flock of nesting geese" << endl;
}


tuition::tuition(string name, int position) :
nonProperty{name, position} {} 

tuition::~tuition() {}

//action when player lands on Tuition
void tuition::squareAction(Player * p) { 
    char choice = 'N';
    cout << p->getName() << ", it's time to pay Tuition!" << endl;

    while (choice != 'C' && choice != 'W' && !cin.fail()) { 
        cout << "Option 1: Please enter 'C' if you wish to pay $300 tuition" << endl;
        cout << "Option 2: Please enter 'W' if you wish to pay 10 percent of your total worth" << endl;
        cin >> choice; 
        if (choice == 'C') { 
            if (300 > p->getMoney()) { 
                cout << "Oops! You don't have $300, you currently have $" << p->getMoney() << endl;
                cout << "Maybe try Option 2..." << endl;
                continue; 
            } else {
                cout << "You paid $300" << endl;
                p->payBank(300); 
                break;            
            }
        } else if (choice == 'W') { 
            p->payBank(p->netWorth() * 10 / 100);
            cout << "You paid $" << (p->netWorth() * 10 / 100) << endl;
            break; 
        } else { 
            cout << "Invalid command" << endl; 
        }
    }
}


coop::coop(string name, int position) :
nonProperty{name, position} {} 

coop::~coop() {} 

//action when player lands on Coop Fee
void coop::squareAction(Player * p) { 
    cout << p->getName() << ", it's time to pay your Coop Fee!" << endl;
    if (150 > p->getMoney()) { 
        cout << "Oops! You don't have $150!" << endl;  
        while (true) { 
            cout << "Type 'bankrupt' to declare bankrupcy" << endl; 
            string cmd; 
            cin >> cmd; 
            if (cmd == "bankrupt") { 
                p->BankruptOweBank(); 
                break;
 
            }
        }
    } else {
        cout << "You paid $150 in Coop Fee" << endl;
        p->payBank(150); 
    }
}

slc::slc(string name, int position):nonProperty{name, position}{}

slc::~slc(){} 

//action when player lands on SLC
void slc::squareAction(Player * p){
    cout << "You are now at SLC!" << endl;
    cout << "Picking up a random movement card from the deck...." << endl;
    int prob1 = 0;
    int prob2 = 0;
    srand(time(NULL)); 
    prob1 = (rand() % 100) + 1;
    prob2 = (rand() % 24) + 1;

    if (prob1 == 1){
        cout << "Woah super lucky! You won a Roll Up the Rim cup! This only happens 1 in 100 times!" << endl;
        p->addCup();
    } else {
        switch(prob2){
            case 1: case 2: case 3:
                cout << "You have to move back 3 squares!" << endl;
                break;
        
            case 4: case 5: case 6: case 7:
                cout << "You have to move back 2 squares!" << endl;
                break;
                
            case 8: case 9: case 10: case 11:
                cout << "You have to move back 1 square!" << endl;
                break;
        
            case 12: case 13: case 14:
                cout << "You have to move forward 1 square!" << endl;
                break;
        
            case 15: case 16: case 17: case 18:
                cout << "You have to move forward 2 squares!" << endl;
                break;
        
            case 19: case 20: case 21: case 22:
                cout << "You have to move forward 3 squares!" << endl;
                break;
        
            case 23:
                cout << "You have to go to DC Tims Line!" << endl;
                break;
        
            case 24:
                cout << "You have to advance to collect OSAP!" << endl;
                break;
    
        }
    }
    
}

nh::nh(string name, int position):nonProperty{name, position}{}

nh::~nh(){}

//action when player lands on Needles Hall
void nh::squareAction(Player * p){
    cout << "You are now at Needles Hall!" << endl;
    cout << "Picking up a random money card from the deck...." << endl;
    int prob1 = 0;
    int prob2 = 0;
    srand(time(NULL)); 
    prob1 = (rand() % 100) + 1;
    prob2 = (rand() % 18) + 1;

    if (prob1 == 1){
        cout << "Woah super lucky! You won a Roll Up the Rim cup! This only happens 1 in 100 times!" << endl;
        p->addCup();
    } else {
        switch(prob2){
            case 1:
                cout << "Unlucky! You lost $200" << endl;
                p->payBank(200);
                break;
        
            case 2: case 3:
                cout << "Unlucky! You lost $100" << endl;
                p->payBank(100);
                break;
                
            case 4: case 5: case 6:
                cout << "Unlucky! You lost $50" << endl;
                p->payBank(50);
                break;
        
            case 7: case 8: case 9: case 10: case 11: case 12:
                cout << "You won $25!" << endl;
                p->addMoney(25);
                break;
        
            case 13: case 14: case 15:
                cout << "You won $50!" << endl;
                p->addMoney(50);
                break;
        
            case 16: case 17:
                cout << "You won $100!" << endl;
                p->addMoney(100);
                break;
        
            case 18:
                cout << "You won $200!" << endl;
                p->addMoney(200);
                break;
        }
    }

}


