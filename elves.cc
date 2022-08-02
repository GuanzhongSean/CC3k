#include "player.h"
#include "elves.h"

Elves::Elves() {
    HP = 140;
    MaxHP = 140;
    Atk = 30;
    Def = 10;
    race = "Elves";
    tempBuffs.clear();
}

string Elves::attack(shared_ptr<Enemy>& e){
    return e->beAttacked(this);
}
