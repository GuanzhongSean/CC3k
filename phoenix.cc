#include "phoenix.h"

using namespace std;

Phoenix::Phoenix(){
    HP = 50;
    Atk = 35;
    Def = 20;
    Gold = 1;
    active = true;
    type = 'X';
}

string Phoenix::attack(shared_ptr<Player>& player) {
    return player->beAttacked(this);
}
