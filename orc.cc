#include "orc.h"
#include "player.h"

Orc::Orc() {
    HP = 180;
    MaxHP = 180;
    Atk = 30;
    Def = 25;
    race = "Orc";
    tempBuffs.clear();
}

void Orc::addGold(float n) {
    gold += n / 2;
}

string Orc::attack(shared_ptr<Enemy>& e) {
    return e->beAttacked(this);
}


