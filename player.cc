#include "player.h"
#include <string>
#include <vector>
#include <cmath>
#include "enemy.h"
#include "vampire.h"
#include "werewolf.h"
#include "troll.h"
#include "goblin.h"
#include "merchant.h"
#include "phoenix.h"
#include "dragon.h"
#include "item.h"
#include <memory>
using namespace std;


int Player::getHP() {
    return HP;
}

int Player::getMaxHP() {
    return MaxHP;
}

int Player::getAtk() {
    return Atk;
}

int Player::getDef() {
    return Def;
}

float Player::getGold() {
    return gold;
}

string Player::getRace() {
    return race;
}

void Player::addGold(float n) {
    gold += n;
}

bool Player::isDead() {
    if (HP <= 0) {
        return true;
    } else {
        return false;
    }
}

void Player::changeHP(int n) {
    if (HP + n >= MaxHP) {
        HP = MaxHP;
    } else {
        HP += n;
    }
}

void Player::changeAtk(int n) {
    if (Atk + n <= 0) {
        Atk = 0;
    } else {
        Atk += n;
    }
}

void Player::changeDef(int n) {
    if (Def + n <= 0) {
        Def = 0;
    } else {
        Def += n;
    }
}

void Player::addTempBuff(string buff) {
    tempBuffs.emplace_back(buff);
}

void Player::clearBuff() {
    for (string s : tempBuffs) {
        if (s == "BA") {
            Atk -= 5;
        } else if (s == "BD") {
            Def -= 5;
        } else if (s == "WA") {
            Atk += 5;
        } else {
            Def += 5;
        }
    }
    tempBuffs.clear();
}



string Player::use(shared_ptr<Item>& i) {
    return i->useItem(*this);
}

string Player::beAttacked(Vampire *x) {
    int damage;
    float A = x->getAtk();
    float Defence = 100.0 / (100.0 + Def);
    if (barrierSuite) {
        damage = ceil(ceil(Defence * A) / 2);
    } else {
        damage = ceil(Defence * A);
    }
    HP -= damage;
    string a = "";
    a += x->get_type();
    a += " deals ";
    a += to_string(damage);
    a += " damage to PC. ";
    return a;
}

string Player::beAttacked(Werewolf *x) {
    int damage;
    float A = x->getAtk();
    float Defence = 100.0 / (100.0 + Def);
    if (barrierSuite) {
        damage = ceil(ceil(Defence * A) / 2);
    } else {
        damage = ceil(Defence * A);
    }
    HP -= damage;
    string a;
    a += x->get_type();
    a += " deals ";
    a += to_string(damage);
    a += " damage to PC.";
    return a;
}

string Player::beAttacked(Troll *x) {
    int damage;
    float A = x->getAtk();
    float Defence = 100.0 / (100.0 + Def);
    if (barrierSuite) {
        damage = ceil(ceil(Defence * A) / 2);
    } else {
        damage = ceil(Defence * A);
    }
    HP -= damage;
    string a;
    a += x->get_type();
    a += " deals ";
    a += to_string(damage);
    a += " damage to PC.";
    return a;
}

string Player::beAttacked(Goblin *x) {
    int damage;
    float A = x->getAtk();
    float Defence = 100.0 / (100.0 + Def);
    if (barrierSuite) {
        damage = ceil(ceil(Defence * A) / 2);
    } else {
        damage = ceil(Defence * A);
    }
    HP -= damage;
    string a;
    a += x->get_type();
    a += " deals ";
    a += to_string(damage);
    a += " damage to PC.";
    return a;
}

string Player::beAttacked(Merchant *x) {
    int damage;
    float A = x->getAtk();
    float Defence = 100.0 / (100.0 + Def);
    if (barrierSuite) {
        damage = ceil(ceil(Defence * A) / 2);
    } else {
        damage = ceil(Defence * A);
    }
    HP -= damage;
    string a;
    a += x->get_type();
    a += " deals ";
    a += to_string(damage);
    a += " damage to PC.";
    return a;
}

string Player::beAttacked(Dragon *x) {
    int damage;
    float A = x->getAtk();
    float Defence = 100.0 / (100.0 + Def);
    if (barrierSuite) {
        damage = ceil(ceil(Defence * A) / 2);
    } else {
        damage = ceil(Defence * A);
    }
    HP -= damage;
    string a;
    a += x->get_type();
    a += " deals ";
    a += to_string(damage);
    a += " damage to PC.";
    return a;
}

string Player::beAttacked(Phoenix *x) {
    int damage;
    float A = x->getAtk();
    float Defence = 100.0 / (100.0 + Def);
    if (barrierSuite) {
        damage = ceil(ceil(Defence * A) / 2);
    } else {
        damage = ceil(Defence * A);
    }
    HP -= damage;
    string a;
    a += x->get_type();
    a += " deals ";
    a += to_string(damage);
    a += " damage to PC.";
    return a;
}

void Player::setAtk(int atk){
    Atk = atk;
}

void Player::setDef(int def){
    Def = def;
}

void Player::setGold(float g){
    gold = g;
}

void Player::setHP(int hp){
    HP = hp;
}

