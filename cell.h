#ifndef _CELL_H_
#define _CELL_H_

#include "enemy.h"
#include "player.h"
#include "item.h"
#include <vector>
#include <string>
#include <memory>
class Pos;

using namespace std;
class Grid;


class Cell {
    int r;
    int c;
    int type; // NA: -1, free: 0, player: 1, item: 2, enemy: 3
    Grid* g;
    shared_ptr<Item> item = nullptr;
    shared_ptr<Enemy> enemy = nullptr;
    shared_ptr<Player> player = nullptr;
    char display;
    char origDisplay;
    bool isStair = false;
    vector<shared_ptr<Cell>> neighbours;
public:
    Cell(int r, int c, Grid *g, char cc);
    void setItem(shared_ptr<Item> i);
    void setEnemy(shared_ptr<Enemy> e);
    void setPlayer(shared_ptr<Player> p);
    shared_ptr<Item>& getItem();
    shared_ptr<Enemy>& getEnemy();
    shared_ptr<Player>& getPlayer();
    void setStair();
    int getType();
    char getDisplay();
    int getR();
    int getC();
    vector<shared_ptr<Cell>> getNeighbours();
    void attach(shared_ptr<Cell>n);
    void update();
    void displayStair();
    void clearCell();
    bool checkStair();
    bool move(int ar, int ac, string& action); // for player
    Pos move(int ar, int ac); // for enemy
    string attack(int ar, int ac);
    string use(int ar, int ac);
};

#endif
