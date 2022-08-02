#include "player.h"
#include "dwarf.h"

Dwarf::Dwarf() {
    HP = 100;
    MaxHP = 100;
    Atk = 20;
    Def = 30;
    race = "Dwarf";
    tempBuffs.clear();
}

void Dwarf::addGold(float n) {
    gold += n * 2;
}

string Dwarf::attack(shared_ptr<Enemy>& e){
    return e->beAttacked(this);
}
