#include <string>
#include <iostream>
#include <fstream>
#include <random>
#include <memory>
#include <vector>
#include "colour.h"
#include "player.h"
#include "enemy.h"
#include "vampire.h"
#include "werewolf.h"
#include "treasure.h"
#include "troll.h"
#include "goblin.h"
#include "merchant.h"
#include "phoenix.h"
#include "item.h"
#include "human.h"
#include "orc.h"
#include "dwarf.h"
#include "elves.h"
#include "dragon.h"
#include "item.h"
#include "potion.h"
#include "barriersuite.h"
#include "grid.h"



using namespace std;


shared_ptr<Cell> Grid::getCell(Pos p){
    return theGrid[p.x][p.y];
}

void Grid::loadInput(char cmd, shared_ptr<Cell> c, char race, shared_ptr<Player> player){
    switch (cmd) {
        case '0' :  c->setItem(shared_ptr<Item>(new RH())); break;
        case '1' :  c->setItem(shared_ptr<Item>(new BA())); break;
        case '2' :  c->setItem(shared_ptr<Item>(new BD())); break;
        case '3' :  c->setItem(shared_ptr<Item>(new PH())); break;
        case '4' :  c->setItem(shared_ptr<Item>(new WA())); break;
        case '5' :  c->setItem(shared_ptr<Item>(new WD())); break;
        case '6' :  c->setItem(shared_ptr<Item>(new Treasure(1))); break;
        case '7' :  c->setItem(shared_ptr<Item>(new Treasure(2))); break;
        case '8' :  c->setItem(shared_ptr<Item>(new Treasure(4))); break;
        case '9' :  c->setItem(shared_ptr<Item>(new Treasure(6,false))); break;
        case 'V' :  {
            c->setEnemy(shared_ptr<Enemy>(new Vampire()));
            enemies.emplace_back(c);
            break;
        }
        case 'W' :  {
            c->setEnemy(shared_ptr<Enemy>(new Werewolf()));
            enemies.emplace_back(c);
            break;
        }
        case 'N' :  {
            c->setEnemy(shared_ptr<Enemy>(new Goblin()));
            enemies.emplace_back(c);
            break;
        }
        case 'M' :  {
            c->setEnemy(shared_ptr<Enemy>(new Merchant()));
            enemies.emplace_back(c);
            break;
        }
        case 'D' :  {
            c->setEnemy(shared_ptr<Enemy>(new Dragon()));
            enemies.emplace_back(c);
            break;
        }
        case 'X' :  {
            c->setEnemy(shared_ptr<Enemy>(new Phoenix()));
            enemies.emplace_back(c);
            break;
        }
        case 'B' :  {
             c->setItem(shared_ptr<Item>(new Treasure(6,false))); break;
        }
        case 'T' :  {
            c->setEnemy(shared_ptr<Enemy>(new Troll()));
            enemies.emplace_back(c);
            break;
        }
        case '\\':  {
            c->setStair();
            theStair = c;
            break;
        }
        case '@': {
            
            if(race != 'N'){
                
                switch(race) {
                    case 'h': c->setPlayer(shared_ptr<Player>(new Human())); break;
                    case 'd': c->setPlayer(shared_ptr<Player>(new Dwarf())); break;
                    case 'e': c->setPlayer(shared_ptr<Player>(new Elves())); break;
                    case 'o': c->setPlayer(shared_ptr<Player>(new Orc())); break;
                } 
            }else {
                c->setPlayer(player);
            }
            thePlayer = c;
            break;
        }
    }
}

void Grid::loadGame(ifstream& archive, char race, shared_ptr<Player> player){
    char in;
    for(int i = 0; i < 25; i++){
        vector<shared_ptr<Cell>> tmp;
        for(int j = 0; j < 79; j++){
            while (true) {
                archive >> noskipws >> in;
                if (in != '\n') {
                    break;
                }
            }
            shared_ptr<Cell> nc;
            Pos p{i,j};
            if(in != '.' && in != '#' && in != '+' && in != '-' && in != '|' && in != ' ') {
                nc = shared_ptr<Cell>(new Cell(i,j,this,'.'));
            }else{
                nc = shared_ptr<Cell>(new Cell(i,j,this,in));
            }
            if(in == '@' && race != 'N') {
                loadInput(in, nc, race);
            }else{
                loadInput(in, nc, race, player);
            }
            tmp.emplace_back(nc);
        }
        theGrid.emplace_back(tmp);
    }
    for(int i = 0; i < 25; i ++){
		for(int j = 0; j < 79; j ++){
			for(int k = -1; k < 2; k++){
				for(int h = -1; h < 2; h++){
					int ni = i+k;
					int nj = j+h;
					if( ni < 0 || ni >= 25){
						continue;
					}
					if( nj < 0 || nj >= 79){
						continue;
					}
					if( ni == 25 && nj == 79){
						continue;
					}
					theGrid[i][j]->attach(theGrid[ni][nj]);
				}
			}
		}
	}

    // Link Dragon with Horde
    for(int i = 0; i < 25; i ++){
		for(int j = 0; j < 79; j ++){
            if(theGrid[i][j]->getDisplay() == 'D' || theGrid[i][j]->getDisplay() == 'B'){
                Pos horde = hordeInrange(i,j);
                theGrid[i][j]->getEnemy()->setHorde(getCell(horde));
            }
        }
    }
}


void Grid::setFloor( ) {
    ifstream format{"layout.txt"};
    char in;
    for(int i = 0; i < 25; i++){
        vector<shared_ptr<Cell>> tmp;
        for(int j = 0; j < 79; j++){
            while (true) {
                format >> noskipws >> in;
                if (in != '\n') {
                    break;
                }
            }
            shared_ptr<Cell> c = shared_ptr<Cell>(new Cell(i,j,this,in));
            tmp.emplace_back(c);
        }
        theGrid.emplace_back(tmp);
    }
    for(int i = 0; i < 25; i ++){
		for(int j = 0; j < 79; j ++){
			for(int k = -1; k < 2; k++){
				for(int h = -1; h < 2; h++){
					int ni = i+k;
					int nj = j+h;
					if( ni < 0 || ni >= 25){
						continue;
					}
					if( nj < 0 || nj >= 79){
						continue;
					}
					if( ni == 25 && nj == 79){
						continue;
					}
					theGrid[i][j]->attach(theGrid[ni][nj]);
				}
			}
		}
	}
}



bool Grid::playerInrange(int r, int c){
    for(int i = -1; i <= 1; i++){
        for(int j = -1; j <= 1; j++){
            Pos p = Pos(r+i, c+j);
            if(getCell(p)->getType() == 1 ){
                return true;
            }
        }
    }
    return false;
}


Pos Grid::hordeInrange(int r, int c){
    for(int i = -1; i <= 1; i++){
        for(int j = -1; j <= 1; j++){
            Pos p = Pos(r+i, c+j);
            if(getCell(p)->getType() == 2){
                if( getCell(p)->getItem()->getVaule() == 6 ){
                    Pos p{r+i,c+j};
                    return p;
                }else{
                    continue;
                
                }
            }else{
                continue;
            }
        }
    }
    return Pos{r,c};
}


void Grid::setEnemies(){
    Pos p{0,0};
    while(true) {
        Pos pa = c.randomCell();
        char x = getCell(pa)->getDisplay();
        if(x == '.' && !getCell(p)->checkStair()){
            p = pa;
            break;
        }
    } 
    int chance = rand() % 18;
    if(chance <= 4) {
        getCell(p)->setEnemy(shared_ptr<Enemy>(new Werewolf()));
        enemies.emplace_back(getCell(p));
    }else if(chance <= 7){
        getCell(p)->setEnemy(shared_ptr<Enemy>(new Vampire()));
        enemies.emplace_back(getCell(p));
    }else if(chance <= 12){
        getCell(p)->setEnemy(shared_ptr<Enemy>(new Goblin()));
        enemies.emplace_back(getCell(p));
    }else if(chance <= 14){
        getCell(p)->setEnemy(shared_ptr<Enemy>(new Troll()));
        enemies.emplace_back(getCell(p));
    }else if(chance <= 16){
        getCell(p)->setEnemy(shared_ptr<Enemy>(new Phoenix()));
        enemies.emplace_back(getCell(p));
    }else if(chance <= 18){
        getCell(p)->setEnemy(shared_ptr<Enemy>(new Merchant()));
        enemies.emplace_back(getCell(p));
    }
    numEnemies += 1;
}

void Grid::setPotions(){
    Pos p{0,0};
    while(true) {
        Pos pa = c.randomCell();
        char x = getCell(pa)->getDisplay();
        if(x == '.' && !getCell(p)->checkStair()){
            p = pa;
            break;
        }
    }
    int whatPotion = rand() % 6;
    if(whatPotion == 0) getCell(p)->setItem(shared_ptr<Item>(new RH()));
    if(whatPotion == 1) getCell(p)->setItem(shared_ptr<Item>(new BA()));
    if(whatPotion == 2) getCell(p)->setItem(shared_ptr<Item>(new BD())); 
    if(whatPotion == 3) getCell(p)->setItem(shared_ptr<Item>(new PH()));
    if(whatPotion == 4) getCell(p)->setItem(shared_ptr<Item>(new WA()));
    if(whatPotion == 5) getCell(p)->setItem(shared_ptr<Item>(new WD()));
    numPotions++;
}

void Grid::setDragon(shared_ptr<Cell> horde){
    Pos newPos{0,0};
    while(true){
        int ra = rand() % 3 - 1;
        int rb = rand() % 3 - 1;
        Pos p = Pos(horde->getR()+ra, horde->getC()+rb);
        char x = getCell(p)->getDisplay();
        if(x == '.' && !getCell(p)->checkStair()){
            newPos = p;
            break;
        }
    }
    getCell(newPos)->setEnemy(shared_ptr<Enemy>(new Dragon()));
    getCell(newPos)->getEnemy()->setHorde(horde);
    enemies.emplace_back(getCell(newPos));
    numEnemies++;
}

void Grid::setTreasures(){
    Pos p{0,0};
    while(true) {
        Pos pa = c.randomCell();
        char x = getCell(pa)->getDisplay();
        if(x == '.' && !getCell(p)->checkStair()){
            p = pa;
            break;
        }
    }
    float whatTreasure;
    int a = rand() % 7;
    if(a <= 4) {
        whatTreasure = 1;
        numTreasure++;
    }else if(a <= 5) {
        whatTreasure = 2;
        numTreasure++;
    }else if(a <= 6){
        whatTreasure = 6;
        numTreasure++;
    }
    if(whatTreasure == 6){
        getCell(p)->setItem(shared_ptr<Item>(new Treasure(whatTreasure, false)));
        setDragon(getCell(p));
    } else {
        getCell(p)->setItem(shared_ptr<Item>(new Treasure(whatTreasure)));
    }
    numTreasure++;
}

void Grid::setBarrierSuite(){
    Pos p{0,0};
    while(true) {
        Pos pa = c.randomCell();
        if(getCell(p)->getType() != 0 || getCell(p)->checkStair()) continue;
        p = pa;
        break;
    }
    getCell(p)->setItem(shared_ptr<Item>(new BarrierSuite()));
    setDragon(getCell(p));
}

void Grid::setPlayer(shared_ptr<Player> origPlayer){
    Pos p = c.randomCell();
    getCell(p)->setPlayer(origPlayer);
    thePlayer = getCell(p);
}

void Grid::setPlayer(char race){
    Pos p = c.randomCell();
    switch(race) {
        case 'h': getCell(p)->setPlayer(shared_ptr<Player>(new Human())); break;
        case 'd': getCell(p)->setPlayer(shared_ptr<Player>(new Dwarf())); break;
        case 'e': getCell(p)->setPlayer(shared_ptr<Player>(new Elves())); break;
        case 'o': getCell(p)->setPlayer(shared_ptr<Player>(new Orc())); break;
    }
    thePlayer = getCell(p);
}

void Grid::setStair(){
    Pos p{0,0};
    while(true) {
        Pos pa = c.randomCell();
        if(getCell(p)->getType() == 1) continue;
        p = pa;
        break;
    }
    getCell(p)->setStair();
    theStair = getCell(p);
}

void Grid::setCompass(){
    size_t random = rand() % enemies.size();
    enemies[random]->getEnemy()->setCompass();
}




void Grid::enemyAction(){
// Check if the Enemy is active
    for (size_t i = 0; i < enemies.size(); i++) {
        if (enemies[i]->getEnemy() == nullptr) {
            continue;
        }

        if(enemies[i]->getEnemy()->isActive()){
            if (enemies[i]->getDisplay() == 'D') {
                shared_ptr<Cell> horde = enemies[i]->getEnemy()->getHorde();
                if (!playerInrange(horde->getR(), horde->getC())) {
                    enemies[i]->getEnemy()->clearActice();
                    continue;
                }
            }
// Check if the Player is in the attack range
            if(playerInrange(enemies[i]->getR(), enemies[i]->getC())) {
                int miss = rand() % 2;
                if(miss) {
                    action += enemies[i]->getEnemy()->get_type();
                    action += " attack misses. ";
                }
                if(!miss) action += enemies[i]->getEnemy()->attack(thePlayer->getPlayer());
            }else{
// Move randomly to a movable spot
                int random1 = rand() % 3 - 1;
                int random2 = rand() % 3 - 1;
                Pos p = enemies[i]->move(random1, random2);
                enemies[i] = getCell(p);
            }
        } else {
// Move randomly
            if (enemies[i]->getDisplay() == 'D') {
                shared_ptr<Cell> horde = enemies[i]->getEnemy()->getHorde();
                if (playerInrange(horde->getR(), horde->getC())) {
                    cout << "a" << endl;
                    enemies[i]->getEnemy()->setActice();
                    continue;
                }
            }
            // if (enemies[i]->getDisplay() == 'D') {
            //     continue;
            // }
            int random1 = rand() % 3 - 1;
            int random2 = rand() % 3 - 1;
            Pos p = enemies[i]->move(random1, random2);
            enemies[i] = getCell(p);
        }
    }
}



shared_ptr<Cell> Grid::getPlayer(){
    return thePlayer;
}



void Grid::playerAction(string input){
    string direction = input;
    if(input[0] == 'u' || input[0] == 'a'){
        direction = input.substr(1);
    }
    int r = 0;
    int c = 0;
    if(direction == "no") {
        r -= 1;
    } else if(direction == "so"){
        r += 1;
    } else if(direction == "we"){
        c -= 1;
    } else if(direction == "ea"){
        c += 1;
    } else if(direction == "nw"){
        r -= 1;
        c -= 1;
    } else if(direction == "ne"){
        r -= 1;
        c += 1;
    } else if(direction == "sw"){
        r += 1;
        c -= 1;
    } else if(direction == "se") {
        r += 1;
        c += 1;
    }
    if(input[0] == 'u') {
        action = thePlayer->use(r,c);
        Pos p{thePlayer->getR() + r, thePlayer->getC() + c};
        getCell(p)->setItem(nullptr);
    } else if(input[0] == 'a') {
        action = thePlayer->attack(r,c);
        Pos p{thePlayer->getR() + r, thePlayer->getC() + c};
        
        if(getCell(p)->getEnemy() != nullptr) {
            if(getCell(p)->getDisplay() == 'M'){
                if(getCell(p)->getEnemy()->isActive()){
                }else{
                    for(auto m : enemies) {
                        if(m->getDisplay() == 'M') m->getEnemy()->setActice();
                    }
                    action += "Merechants become Hostile! ";
                }
            } 
            if (getCell(p)->getEnemy()->isDead()) {
                thePlayer->getPlayer()->addGold(getCell(p)->getEnemy()->dropGold());
                if (getCell(p)->getEnemy()->hasCompass()) {
                    getCell(p)->setEnemy(nullptr);
                    theStair->displayStair();
                    action += "(Compass found) ";
                } else {
                    bool Mere = (getCell(p)->getDisplay() == 'M');
                    getCell(p)->setEnemy(nullptr);
                    if(Mere){
                        getCell(p)->setItem(shared_ptr<Item>(new Treasure(4)));
                    }
                }
            }
        }
    }else if(input[0] == 't'){ 
        action = "PC transfered ";
        int R = stoi(input.substr(1,2));
        int C = stoi(input.substr(3,4));
        Pos p{R,C};
        getCell(p)->setPlayer(thePlayer->getPlayer());
        thePlayer->clearCell();
        thePlayer = getCell(p);
    }else {
        bool x = thePlayer->move(r, c, action);
        if (x) {
            Pos p{thePlayer->getR() + r, thePlayer->getC() + c};
            thePlayer = getCell(p);
        }
    }
}

void Grid::clearFloor(){
    enemies.clear();
    theStair = nullptr;
    thePlayer = nullptr;
    numTreasure = 0;
    numPotions = 0;
    numEnemies = 0;
    action = "";
    theGrid.clear();
}



void Grid::init(char race){
    clearFloor();
    setFloor();
    setChamber();
    setPlayer(race);
    if(theStair == nullptr) setStair();
    while(numTreasure <= 10) setTreasures();
    while(numEnemies <= 20) setEnemies();
    while(numPotions <= 10) setPotions();
    setCompass();
      
}

void Grid::init(shared_ptr<Player> origPlayer){
    clearFloor();
    setFloor();
    setChamber();
    setPlayer(origPlayer);
    if(theStair == nullptr) setStair();
    while(numTreasure <= 10) setTreasures();
    while(numEnemies <= 20) setEnemies();
    while(numPotions <= 10) setPotions();
    setCompass();
}

bool Grid::update(){
    if(thePlayer->checkStair()) {
        return true;
    }
    enemyAction();
    return false;
}

void Grid::setChamber(){
    for(auto r : theGrid){
        for (auto ce : r) {
            if (ce->getDisplay() == '.') {
                Pos p{ce->getR(), ce->getC()};
                c.attachChamber(p);
            }
        }
    }
}

void Grid::printMap(){
    for(int i = 0; i < 25; i++) {
        for(int j = 0; j < 79; j++) {
            if(theGrid[i][j]->getDisplay() == 'G'){
                cout << YELLOW << theGrid[i][j]->getDisplay() << RESET;
            }else if(theGrid[i][j]->getDisplay() == 'P'){
                cout << GREEN << theGrid[i][j]->getDisplay() << RESET;
            }else if(theGrid[i][j]->getType() == 1){
                cout << P << theGrid[i][j]->getDisplay() << RESET;
            }else if(theGrid[i][j]->getType() == 3){
                cout << RED << theGrid[i][j]->getDisplay() << RESET;
            }else if(theGrid[i][j]->getDisplay() == 'B'){
                cout << BLUE << theGrid[i][j]->getDisplay() << RESET;
            }else if(theGrid[i][j]->checkStair()){
                //cout << "S";
                cout << '.';
            }
            else{
                cout << theGrid[i][j]->getDisplay();
            }
            // if(theGrid[i][j]->getType() == 3){
            //     if(theGrid[i][j]->getEnemy()->hasCompass()){
            //         cout << "C";
            //         continue;
            //     }
            // }
            
        //     if (theGrid[i][j]->getType() == -1) {
        //          cout << "-";
        //     } else {
        //         cout << theGrid[i][j]->getType();
        //     }
        }
        cout << endl;
    }
    cout << "Race: " << thePlayer->getPlayer()->getRace() << " Gold: " << thePlayer->getPlayer()->getGold();
    for (int i = 0; i < 50; i++) {
        cout << " ";
    }
    cout << "Floor: " << level;
    cout << endl;
    cout << "HP: " << thePlayer->getPlayer()->getHP() << endl;
    cout << "Atk: " << thePlayer->getPlayer()->getAtk() << endl;
    cout << "Def: " << thePlayer->getPlayer()->getDef() << endl;
    cout << "Action: " << action << endl;
    action = "";
}

vector<vector<shared_ptr<Cell>>> Grid::getGrid(){
    return theGrid;
}
