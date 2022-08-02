#ifndef __POTION_H__
#define __POTION_H__
#include "item.h"
#include "player.h"
#include <string>

using namespace std;

class Potion: public Item{
    float value = 0;
public:
    Potion(string real_name, float);
    float getVaule() override;
    virtual string useItem(Player &player) = 0;
    

};

class RH: public Potion{   
public:
    RH();
    
    string useItem(Player &player) override;
};

class BA: public Potion{
public:
    BA();
    string useItem(Player &player) override;
};

class BD: public Potion{

public:
    BD();
    string useItem(Player &player) override;
};

class PH: public Potion{

public:
    PH();
    string useItem(Player &player) override;
};

class WA: public Potion{

public:
    WA();
    string useItem(Player &player) override;
};

class WD: public Potion{

public:
    WD();
    string useItem(Player &player) override;
};

#endif
