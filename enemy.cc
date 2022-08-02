#include "enemy.h"
#include <cmath>
#include <iostream>
#include "player.h"
#include "human.h"
#include "dwarf.h"
#include "elves.h"
#include "orc.h"


using namespace std;


string Enemy::beAttacked(Human* player) {
    string info = "PC deals ";
    float A = player->getAtk();
    float Defence = 100.0 / (100.0 + Def);
    int damage = ceil(Defence * A);
    HP -= damage;
    info += to_string(damage); 
    info += " damge to ";
    info += type;
    info += " (";
    info += to_string(HP);
    info += " HP).";
    if (HP <= 0) {
        info = "PC has slained a ";
        info += type;
        info += ". ";
    }
    return info; 
}

string Enemy::beAttacked(Dwarf* player) {
    string info = "PC deals ";
    float A = player->getAtk();
    float Defence = 100.0 / (100.0 + Def);
    int damage = ceil(Defence * A);
    HP -= damage;
    info += to_string(damage); 
    info += " damge to ";
    info += type;
    info += " (";
    info += to_string(HP);
    info += " HP).";
    if (HP <= 0) {
        info = "PC has slained a ";
        info += type;
        info += ". ";
    }
    return info; 
}

string Enemy::beAttacked(Elves* player) {
    string info = "PC deals ";
    float A = player->getAtk();
    float Defence = 100.0 / (100.0 + Def);
    int damage = ceil(Defence * A);
    HP -= damage;
    info += to_string(damage); 
    info += " damge to ";
    info += type;
    info += " (";
    info += to_string(HP);
    info += " HP).";
    if (HP <= 0) {
        info = "PC has slained a ";
        info += type;
        info += ". ";
    }
    return info; 
}

string Enemy::beAttacked(Orc* player) {
    string info = "PC deals ";
    float A = player->getAtk();
    float Defence = 100.0 / (100.0 + Def);
    int damage = ceil(Defence * A);
    HP -= damage;
    info += to_string(damage); 
    info += " damge to ";
    info += type;
    info += " (";
    info += to_string(HP);
    info += " HP).";
    if (HP <= 0) {
        info = "PC has slained a ";
        info += type;
        info += ". ";
    }
    return info; 
}

float Enemy::dropGold() {
    return Gold;
}

int Enemy::getHP() {
    return HP;
}

int Enemy::getAtk() {
    return Atk;
}

int Enemy::getDef() {
    return Def;
}

char Enemy::get_type() {
    return type;
}

bool Enemy::isDead() {
    return HP <= 0;
}

bool Enemy::isActive() {
    return active;
}

void Enemy::setActice() {
    active = true;
}

void Enemy::clearActice() {
    active = false;
}

void Enemy::setCompass() {
    compass = true;
}

bool Enemy::hasCompass(){
    return compass;
}
