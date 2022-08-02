#include "merchant.h"
#include <memory>

using namespace std;

Merchant::Merchant(){
    HP = 30;
    Atk = 70;
    Def = 5;
    Gold = 4;
    active = false;
    type = 'M';
}


string Merchant::attack(shared_ptr<Player>& player) {
    return player->beAttacked(this);
}



// void Merchant::setHostile(){
//     hostile = true;
// }

// bool Merchant::isHostile(){
//     return hostile;
// }


