#include "dragon.h"
#include "player.h"

using namespace std;

Dragon::Dragon(){
    HP = 150;
    Atk = 20;
    Def = 20;
    Gold = 0;
    active = false;
    type = 'D';
    horde = nullptr;
}

void Dragon::setHorde(shared_ptr<Cell> h){
    horde = h;
}

shared_ptr<Cell> Dragon::getHorde(){
    return horde;
}

string Dragon::attack(shared_ptr<Player>& player) {
    return player->beAttacked(this);
}

bool Dragon::isDead() {
    if (HP <= 0) {
        horde->getItem()->changeState();
    }
    return HP <= 0;
}
