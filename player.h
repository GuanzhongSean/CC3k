#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <string>
#include <vector>
#include <memory>
// #include "enemy.h"
// #include "vampire.h"
// #include "werewolf.h"
// #include "troll.h"
// #include "goblin.h"
// #include "merchant.h"
// #include "phoenix.h"
// #include "item.h"
class Item;
class Dragon;
class Vampire;
class Goblin;
class Troll;
class Phoenix;
class Merchant;
class Werewolf;
class Enemy;
class Cell;
using namespace std;

class Player {
protected:
    int HP;
    int MaxHP;
    int Atk;
    int Def;
    string race;
    float gold = 0;
    vector<string> tempBuffs;
public:
    int getHP();
    int getMaxHP();
    int getAtk();
    int getDef();
    string getRace();
    float getGold();
    void setHP(int);
    void setAtk(int);
    void setDef(int);
    void setGold(float) ;
    bool isDead();
    bool compass = false;
    bool barrierSuite = false;
    virtual void addGold(float n);
    void changeHP(int n);
    void changeAtk(int n);
    void changeDef(int n);
    void addTempBuff(string buff);
    void clearBuff();
    virtual string attack(shared_ptr<Enemy>& e) = 0;
    string use(shared_ptr<Item>& i);
    string beAttacked(Vampire *x);
    string beAttacked(Werewolf *x);
    string beAttacked(Troll *x);
    string beAttacked(Goblin *x);
    string beAttacked(Merchant *x);
    string beAttacked(Dragon *x);
    string beAttacked(Phoenix *x);
};

#endif
