#include "chamber.h"

#include <string>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

Pos::Pos(int x, int y): x(x), y(y) {}

Pos Chamber::randomCell(){
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine rng{seed};
    shuffle(chamberCell.begin(), chamberCell.end(), rng );
    int select = rand() % totalCells;
    return chamberCell[select];
}

void Chamber::attachChamber(Pos p){
    chamberCell.emplace_back(p);
    // // Chamber 1
    // for(int i = 3;i <= 28; i++){
    //     for(int j = 3;j <= 6; j++){
    //         Pos cell = Pos(i, j);
    //         chamberCell.emplace_back(cell);
    //     }
    // }

    // // Chamber 2
    // for(int i = 38; i <= 49; i++){
    //     for(int j = 10; j <= 12; j++){
    //         Pos cell = Pos(i, j);
    //         chamberCell.emplace_back(cell);
    //     }
    // }


    // // Chamber 3
    // for(int i = 4; i <= 24; i++){
    //     for(int j = 15; j <= 21; j++){
    //         Pos cell = Pos(i, j);
    //         chamberCell.emplace_back(cell);
    //     }
    // }


    // // Chamber 4
    // for(int i = 65; i <= 75; i++){
    //     for(int j = 16; j <= 21; j++){
    //         Pos cell = Pos(i,j);
    //         chamberCell.emplace_back(cell);
    //     }
    // }
    // for(int i = 37; i <= 64; i++){
    //     for(int j = 19; j <= 21; j++){
    //         Pos cell = Pos(i,j);
    //         chamberCell.emplace_back(cell);
    //     }
    // }

    // // Chamber 5
    // for(int i = 39; i <= 61; i++){
    //     for(int j = 3; j<= 6; j++){
    //         Pos cell = Pos(i,j);
    //         chamberCell.emplace_back(cell);
    //     }
    // }
    // for(int i = 61; i <= 75; i++){
    //     for(int j = 7; j <= 12; j++){
    //         Pos cell = Pos(i,j);
    //         chamberCell.emplace_back(cell);
    //     }
    // }
    // for(int i = 62; i <= 69; i++){
    //     int j = 5;
    //     Pos cell = Pos(i,j);
    //     chamberCell.emplace_back(cell);
    // }
    // for(int i = 62; i <= 72; i++){
    //     int j = 6;
    //     Pos cell = Pos(i,j);
    //     chamberCell.emplace_back(cell);
    // }
}
