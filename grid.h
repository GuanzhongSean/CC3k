#ifndef _GRID_H_
#define _GRID_H_

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include "player.h"
#include "enemy.h"
#include "item.h"
#include "chamber.h"
#include "cell.h"

using namespace std;



class Grid {
    int numEnemies = 0;
    int numPotions = 0;
    int numTreasure = 0;
    vector<vector<shared_ptr<Cell>>> theGrid;
    vector<shared_ptr<Cell>> enemies;
    shared_ptr<Cell> thePlayer;
    shared_ptr<Cell> theStair;
    Chamber c;
    Pos hordeInrange(int, int);
    bool playerInrange(int, int);
public:
    string action;
    static int level;
    void init(char);
    void init(shared_ptr<Player> );
    void loadGame(ifstream&, char, shared_ptr<Player> = nullptr);
    void loadInput(char, shared_ptr<Cell>, char, shared_ptr<Player> = nullptr);
    void saveGame();
    bool update();
    void setFloor();
    void setEnemies();
    void setStair();
    void setPotions();
    void setTreasures();
    void setCompass();
    void setDragon(shared_ptr<Cell>);
    void setPlayer(char);
    void setPlayer(shared_ptr<Player>);
    void setBarrierSuite();
    void setChamber();
    void enemyAction();
    void playerAction(string);
    void printMap();
    void clearFloor();
    shared_ptr<Cell> getPlayer();
    shared_ptr<Cell> getStair();
    shared_ptr<Cell> getCell(Pos);
    vector<vector<shared_ptr<Cell>>> getGrid();
};


#endif
