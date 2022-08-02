#include "player.h"
#include "human.h"

Human::Human() {
    HP = 140;
    MaxHP = 140;
    Atk = 20;
    Def = 20;
    race = "Human";
    tempBuffs.clear();
}


string Human::attack(shared_ptr<Enemy>& e) {
    return e->beAttacked(this);
}

