#ifndef _ENEMY_H_
#define _ENEMY_H_
#include <string>
#include <memory>
#include "grid.h"
class Cell;
class Human;
class Dwarf;
class Elves;
class Orc;
class Player;

using namespace std;

class Enemy {
protected:
    int HP;
    int Atk;
    int Def;
    float Gold;
    bool active;
    bool compass = false;
    char type;
public:    
    string beAttacked( Human* );
    string beAttacked( Dwarf* );
    string beAttacked( Elves* );
    string beAttacked( Orc* );
    virtual string attack( shared_ptr<Player>& player ) = 0;
    float dropGold();
    int getHP();
    int getAtk();
    int getDef();
    char get_type();
    virtual bool isDead();
    bool isActive();
    bool hasCompass();
    void setActice();
    void clearActice();
    void setCompass();
    virtual void setHorde(shared_ptr<Cell>) {return;}
    virtual shared_ptr<Cell> getHorde() {return nullptr;}
};

#endif
