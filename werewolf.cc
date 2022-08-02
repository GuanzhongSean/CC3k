#include "werewolf.h"
#include "player.h"
using namespace std;

Werewolf::Werewolf(){
    HP = 120;
    Atk = 30;
    Def = 5;
    Gold = 1;
    active = true;
    type = 'W';
}


string Werewolf::attack(shared_ptr<Player>& player) {
    return player->beAttacked(this);
}
