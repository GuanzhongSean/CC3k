#include "troll.h"

using namespace std;

Troll::Troll(){
    HP = 120;
    Atk = 25;
    Def = 15;
    Gold = 1;
    active = true;
    type = 'T';
}


string Troll::attack(shared_ptr<Player>& player) {
    return player->beAttacked(this);
}
