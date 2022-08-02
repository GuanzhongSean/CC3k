#include <iostream>
#include <string>
#include "barriersuite.h"

using namespace std;

BarrierSuite::BarrierSuite(bool is_dead): Item('B', "B"), is_dead{is_dead}{}

void BarrierSuite::setIs_dead(bool status) {
    is_dead = status;
}

string BarrierSuite::useItem(Player &player){
    if (is_dead){
        player.barrierSuite = true;
        return "The player picked up the barrier suite. ";
    } else {
        return "The dragon still alive. ";
    }
}

float BarrierSuite::getVaule(){
    return 100;
}

