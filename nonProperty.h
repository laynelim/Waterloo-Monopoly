#ifndef _NON_PROPERTY_H_
#define _NON_PROPERTY_H_ 

#include <iostream> 
#include <string>
#include "square.h"

class nonProperty : public Square { 
    public: 
        nonProperty(std::string name, int position); 
        ~nonProperty(); 
        virtual void squareAction(Player * p) = 0;
};

class collectOsap : public nonProperty { 
    public: 
        collectOsap(std::string name, int position);
        ~collectOsap(); 
        void squareAction(Player * p) override; 
};

class timsLine : public nonProperty { 
    public: 
        timsLine(std::string name, int position); 
        ~timsLine();
        void squareAction(Player * p) override; 
};

class gotoTims : public nonProperty { 
    public: 
        gotoTims(std::string name, int position);
        ~gotoTims(); 
        void squareAction(Player * p) override;
};

class gooseNesting : public nonProperty { 
    public: 
        gooseNesting(std::string name, int position);
        ~gooseNesting(); 
        void squareAction(Player * p ) override; 
};

class tuition : public nonProperty { 
    public: 
        tuition(std::string name, int position);
        ~tuition(); 
        void squareAction(Player * p) override; 
};

class coop : public nonProperty { 
    public: 
        coop(std::string name, int position);
        ~coop(); 
        void squareAction(Player * p) override; 
};

class slc : public nonProperty { 
    public: 
        slc(std::string name, int position);
        ~slc(); 
        void squareAction(Player * p) override; 
};

class nh : public nonProperty { 
    public: 
        nh(std::string name, int position);
        ~nh(); 
        void squareAction(Player * p) override; 
};

#endif
