#include "goblin.h"

using namespace std;

Goblin::Goblin(){
    HP = 70;
    Atk = 5;
    Def = 10;
    Gold = 1;
    active = true;
    type = 'N';
}

string Goblin::attack(shared_ptr<Player>& player) {
    return player->beAttacked(this);
}

