#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <random>
#include "game.h"

using namespace std;



int main(int argc, char* argv[]){
    Game theGame;
    if(argc == 1){
        theGame.playGame();
    }else if(argc == 2){
        ifstream map;
        map.exceptions (ifstream::badbit);
        try{
            map.open(argv[1]);
            string fail = "fail";
            if(map.fail()) {
                throw(fail);
            }else {
                cout << "Map " << argv[1] << " has been load! " << endl;
                theGame.playGame(map);
            }
        }catch(const string){
            cerr << "Filename invaild or no read permission." << endl;
        }
        map.close();
        
    }else if(argc == 3){
        ifstream map;
        string data(argv[1]);
        data = "data_" + data;
        map.exceptions (ifstream::badbit);
        try{
            map.open(argv[1]);
            string fail = "fail";
            if(map.fail()) {
                throw(fail);
            }else {
                cout << "Game " << argv[1] << " has been load! " << endl;
                theGame.playGame(map, data);
            }
        }catch(const string){
            cerr << "Filename invaild or no read permission." << endl;
        }
        map.close();
    }else{
        cerr << "invaild type" << endl;
    }

    return 0;
}
