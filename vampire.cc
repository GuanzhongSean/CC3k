#include "vampire.h"



using namespace std;



Vampire::Vampire(){
    HP = 50;
    Atk = 25;
    Def = 25;
    Gold = 1;
    active = true;
    type = 'V';
}


string Vampire::attack(shared_ptr<Player>& player) {
    return player->beAttacked(this);
}
