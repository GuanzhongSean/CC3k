#ifndef GAME_H_
#define GAME_H_
#include <string>
#include <iostream>
#include <fstream>
#include "grid.h"

using namespace std;


class Game {
    bool checkInput(string);
public:
    void playGame();
    void playGame(ifstream&);
    void playGame(ifstream&, string);
    void saveGame(Grid& ,string filename = "");
    void playDLC();
    
};




#endif
