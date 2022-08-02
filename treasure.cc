#include <iostream>
#include <string>
#include "treasure.h"
#include <sstream>

using namespace std;

string Treasure::real_name(float v) {
    if (v == 1) {
        return "a normal pile of gold";
    } else if (v == 2) {
        return "a small hoard of gold";
    } else if (v == 4) {
        return "a merchant hoard of gold";
    } else {
        return "a dragon hoard of gold";
    }
}

Treasure::Treasure(float Gvalue, bool is_dead): Item('G', real_name(Gvalue)), Gvalue{Gvalue}, is_dead{is_dead}{}

void Treasure::setIs_dead(bool status){
    is_dead = status;
}

string Treasure::useItem(Player &player){
    if (is_dead){
        player.addGold(Gvalue);
        string outp = "PC gets ";
        int x = Gvalue;
        outp += to_string(x);
        outp.append(" Gold. ");
        return outp;
    } else {
        return "The dragon is still alive. ";
    }
    return " ";
}

float Treasure::getVaule(){
    return Gvalue;
}
