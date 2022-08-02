#include "cell.h"
#include "enemy.h"
#include "player.h"
#include "item.h"
#include "grid.h"
#include "dragon.h"
#include <iostream>
#include <vector>
#include <string>
#include <memory>

using namespace std;

Cell::Cell(int r, int c, Grid *g, char cc):
r{r}, c{c}, g{g}, display{cc}, origDisplay{cc} {
    if (cc == '.' || cc == '+' || cc == '#') {
        type = 0;
    } else {
        type = -1;
    }
}

bool Cell::checkStair(){
    return isStair;
}

void Cell::setItem(shared_ptr<Item> i) {
    item = i;
    if (i != nullptr) {
        type = 2;
    } else {
        type = 0;
    }
    update();
}

void Cell::setEnemy(shared_ptr<Enemy> e) {
    enemy = e;
    if (e != nullptr) {
        type = 3;
    } else {
        type = 0;
    }
    update();
}

void Cell::setPlayer(shared_ptr<Player> p) {
    player = p;
    if (p != nullptr) {
        type = 1;
    } else {
        type = 0;
    }
    update();
}

void Cell::setStair() {
    isStair = true;
}

int Cell::getType() {
    return type;
}

int Cell::getR() {
    return r;
}

int Cell::getC() {
    return c;
}

shared_ptr<Item>& Cell::getItem() {
    return item;
}

shared_ptr<Enemy>& Cell::getEnemy() {
    return enemy;
}

shared_ptr<Player>& Cell::getPlayer() {
    return player;
}

vector<shared_ptr<Cell>> Cell::getNeighbours() {
    return neighbours;
}
char Cell::getDisplay() {
    return display;
}

void Cell::attach(shared_ptr<Cell>n) {
    neighbours.emplace_back(n);
}

void Cell::update() {
    if (type == 0) {
        display = origDisplay;
    } else if (type == 1) {
        display = '@';
    } else if (type == 2) {
        display = item->getName();
    } else if (type == 3) {
        display = enemy->get_type();
    }
}

void Cell::displayStair() {
    origDisplay = '/';
    if (type == 0) {
        display = '/';
    }
}

bool Cell::move(int ar, int ac, string& action) {
    if (type != 1) {
        return false;
    }

    if (ac == 0 && ar == 0) {
        return false;
    }

    string direction;
    if (ar == 0 && ac == 0) {
        return false;
    } else if (ar == 1 && ac == 1) {
        direction = "Southeast";
    } else if (ar == 1 && ac == 0) {
        direction = "South";
    } else if (ar == 1 && ac == -1) {
        direction = "Southwest";
    } else if (ar == 0 && ac == 1) {
        direction = "East";
    } else if (ar == 0 && ac == -1) {
        direction = "West";
    } else if (ar == -1 && ac == 1) {
        direction = "Northeast"; 
    } else if (ar == -1 && ac == 0) {
        direction = "North";
    } else {
        direction = "Northwest";
    }
    int newr = r + ar;
    int newc = c + ac;
    if (newr < 0 || newr >= 25 || newc < 0 || newc >= 79) {
        return false;
    }
    Pos p{newr, newc};
    shared_ptr<Cell>nextPosition = g->getCell(p);
    if (nextPosition->getType() == 0) {
        nextPosition->setPlayer(player);
        player = nullptr;
        type = 0;
        nextPosition->update();
        update();
        action = "PC moves ";
        action += direction;
        for (auto cc : nextPosition->getNeighbours()) {
            if (cc->getDisplay() == 'B') {
                action += " and sees Barrier Suit";
                break;
            } else if (cc->getDisplay() == 'P') {
                action += " and sees an unknown potion";
                break;
            }
        }
        action += ". ";
        return true;
    } else if (nextPosition->getType() == 2) {
        if (nextPosition->getDisplay() == 'P') {
            action = "There is a potion in this direction. ";
            return false;
        }
        action = player->use(nextPosition->getItem());
        if (action == "The dragon is still alive. ") {
            return false;
        } else {
            nextPosition->setItem(nullptr);
            nextPosition->setPlayer(player);
            type = 0;
            player = nullptr;
            nextPosition->update();
            update();
            return true;
        }
    } else {
        action = "Invalid Direction. ";
        return false;
    }
}

Pos Cell::move(int ar, int ac) {
    if (type != 3) {
        return Pos{r, c};
    }

    if (ar == 0 && ac == 0) {
        return Pos{r, c};
    }

    int newr;
    int newc;

    shared_ptr<Cell> nextPosition;

    if (display == 'D') {
        shared_ptr<Cell>treasure = enemy->getHorde();
        int tr = treasure->getR();
        int tc = treasure->getC();
        newr = tr + ar;
        newc = tc + ac;
    } else {
        newr = r + ar;
        newc = c + ac;
    }

    if (newr < 0 || newr >= 25 || newc < 0 || newc >= 79) {
        return Pos{r, c};
    }
    Pos p{newr, newc};
    nextPosition = g->getCell(p);
    if (nextPosition->getDisplay() == '.') {
        nextPosition->setEnemy(enemy);
        enemy = nullptr;
        type = 0;
        nextPosition->update();
        update();
        return p;
    } else {
        return Pos{r, c};
    }
}

string Cell::attack(int ar, int ac) {
    int newr = r + ar;
    int newc = c + ac;
    if (newr < 0 || newr >= 25 || newc < 0 || newc >= 79) {
        string str = "Invalid object. ";
        return str;
    }

    Pos p{newr, newc};
    shared_ptr<Cell>nextPosition = g->getCell(p);
    if (nextPosition->getType() == 3) {
        string str = player->attack(nextPosition->getEnemy());
        return str;
    } else {
        string str = "Invalid object. ";
        return str;
    }
}

string Cell::use(int ar, int ac) {
    int newr = r + ar;
    int newc = c + ac;
    if (newr < 0 || newr >= 25 || newc < 0 || newc >= 79) {
        string str = "Invalid Potion. ";
        return str;
    }

    Pos p{newr, newc};
    shared_ptr<Cell>nextPosition = g->getCell(p);
    if (nextPosition->getDisplay() == 'P') {
        return player->use(nextPosition->getItem());
    } else {
        string str = "Invalid Potion. ";
        return str;
    }
}

void Cell::clearCell(){
    player = nullptr;
    type = 0;
    update();

}
