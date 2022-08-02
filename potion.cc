#include <iostream>
#include <string>
#include "potion.h"

using namespace std;

Potion::Potion(string Real_name, float v): Item('P', Real_name), value(v) {}

float Potion::getVaule(){
    return value;
}


RH::RH(): Potion("RH", 10){
    
}

string RH::useItem(Player &p){
    p.changeHP(10);
    return "Player used RH. ";
}


BA::BA(): Potion("BA", 11){}

string BA::useItem(Player &p){
    p.changeAtk(5);
    p.addTempBuff("BA");
    return "Player used BA. ";
}



BD::BD(): Potion("BD", 12){}

string BD::useItem(Player &p){
    p.changeDef(5);
    p.addTempBuff("BD");
    return "Player used BD. ";
}



PH::PH(): Potion("PH", 13){}

string PH::useItem(Player &p){
    if(p.getRace() == "Elves"){
        p.changeHP(10);
    } else {
        p.changeHP(-10);
    }

    return "Player used PH. ";
}



WA::WA(): Potion("WA", 14){}

string WA::useItem(Player &p){
    if(p.getRace() == "Elves"){
        p.changeAtk(5);
        p.addTempBuff("BA");
    } else {
        p.changeAtk(-5);
        p.addTempBuff("WA");
    }

    return "Player used WA. ";
}


WD::WD(): Potion("WD", 15){}

string WD::useItem(Player &p){

    if(p.getRace() == "Elves"){
        p.changeDef(5);
        p.addTempBuff("BD");
    } else {
        p.changeDef(-5);
        p.addTempBuff("WD");
    }

    return "Player used WD. ";
}


