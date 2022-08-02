#include <iostream>
#include <cctype>
#include <string>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <random>
#include "game.h"
#include "grid.h"
#include "cell.h"
#include "item.h"
#include "player.h"
#include "enemy.h"
#include "barriersuite.h"

using namespace std;

int Grid::level = 1;

bool Game::checkInput(string in){
    string input = in;
    if(in[0] == 't') return true;
    if(in[0] == 'a' || in[0] == 'u'){
        input = in.substr(1);
    }
    if(input == "no" || input == "so" || input == "ea" || input == "we"
        || input == "ne" || input == "nw" || input == "se" || input == "sw"){
            return true;
    }
    return false;
}

void Game::playGame() {
    string input;
    char race;
    Grid g;
    shared_ptr<Cell> player;
    int barriersuite = 0;
    bool restart = false;
    cout << "====================================\n";
    cout << "          Welcome to CC3k!\n";
    cout << "====================================\n";
    while(true){ 
        while (g.level <= 5) {

            
            // if(!barriersuite){
            //     int chance = rand() % 1;
            //     if (chance || g.level == 1) barriersuite = 1;
            // }
            
                      
            
            if(g.level == 1) {
                cout << "Choose a race: human/dwarf/elves/orc (h/d/e/o)" << endl;
                cin >> race;
                if(race == 'q'){
                    return;
                }
                g.init(race);
                if(barriersuite == 1) {
                    g.setBarrierSuite();
                    barriersuite++;
                }
                player = g.getPlayer();
                g.action = "Player character has spawned.";            
            }
            if(g.level != 1){
                g.init(player->getPlayer());
                if(barriersuite == 1) {
                    g.setBarrierSuite();
                    barriersuite++;
                }
                g.action += "PC find the Stair and has arrived to floor ";
                g.action += to_string(g.level);
                g.action += "! (All Buff cleared) ";
            }

            bool sc = true;
            while(player->getPlayer()->getHP() > 0) {
                player->checkStair();
                string d;
                if (sc) {
                    g.printMap();
                }
                sc = false;
                cout << "Command: ";
                cin >> input;
                
                if(input == "r") {
                    cout << "================================\n";
                    cout << "         PC reset the game\n";
                    cout << "================================\n";
                    g.level = 1;
                    restart = true;
                    break;
                } else if (input == "q") {
                    return ;
                } else if (input == "s"){
                    cout << "Where you wish to save: ";
                    string filename;
                    cin >> filename;
                    saveGame(g,filename);
                    cout << "Saved! " << endl;
                    return;
                } else if (checkInput(input)){
                    g.playerAction(input);
                    player = g.getPlayer();
                    sc = true;
                }
                if (sc){
                    bool x = g.update();
                    if(x) {
                        player->getPlayer()->clearBuff();
                        break;
                    }   
                } else {
                    cout << "Invalid Input." << endl;
                }
            }
            if (player->getPlayer()->getHP() <= 0) {
                cout << "==================================\n";
                cout << "                                  \n";
                cout << "             YOU lOST!\n";
                cout << "                                  \n";
                cout << "                                  \n";
                cout << "   Would you like to play again?\n";
                cout << "         Y(yes) or N(no)  \n";
                cout << "                                  \n";
                cout << "                                  \n";
                cout << "==================================\n";
                cout << "Command: ";
                cin >> input;
                if(input == "Y") {
                    g.level = 1;
                    break;
                }else{
                    return;
                }
            }
            if (restart) {
                restart = false;
                break;
            }
            g.level++;
            //reset player
        }
        if (g.level == 6) {
            int gold = player->getPlayer()->getGold();
            cout << "============================\n";
            cout << "            YOU WIN.\n";
            cout << "       FINAL SCORE: " << gold  << "\n";
            cout << "============================\n\n";
            return ;          
        }
    }
}

void Game::playGame(ifstream& map){
    string input;
    char race;
    Grid g;
    shared_ptr<Cell> player;
    int barriersuite = 0;
    bool restart = false;
    cout << "====================================\n";
    cout << "          Welcome to CC3k!\n";
    cout << "====================================\n";
    while(true){ 


        while (g.level <= 5) {

            
            if(!barriersuite){
                int chance = rand() % 1;
                if (chance || g.level == 5) barriersuite = 1;
            }
            
                      
            if(g.level == 1) {
                cout << "Choose a race: human/dwarf/elves/orc (h/d/e/o)" << endl;
                cin >> race;
                if(race == 'q'){
                    return;
                }
                g.loadGame(map,race);
                map.close();
                if(barriersuite == 1) {
                    g.setBarrierSuite();
                    barriersuite++;
                }
                player = g.getPlayer();
                g.action = "Player character has spawned.";            
            }
            if(g.level != 1){
                g.loadGame(map,'N',player->getPlayer());
                map.close();
                if(barriersuite == 1) {
                    g.setBarrierSuite();
                    barriersuite++;
                }
                g.action += "PC find the Stair and has arrived to floor ";
                g.action += to_string(g.level);
                g.action += "! (All Buff cleared) ";
            }

            bool sc = true;
            while(player->getPlayer()->getHP() > 0) {
                player->checkStair();
                string d;
                if (sc) {
                    g.printMap();
                }
                sc = false;
                cout << "Command: ";
                cin >> input;
                
                if(input == "r") {
                    cout << "================================\n";
                    cout << "         PC reset the game\n";
                    cout << "================================\n";
                    g.level = 1;
                    restart = true;
                    break;
                } else if (input == "q") {
                    return;
                } else if (input == "s"){
                    cout << "Where you wish to save: ";
                    string filename;
                    cin >> filename;
                    saveGame(g,filename);
                    cout << "Saved! " << endl;
                    return;
                } else if (checkInput(input)){
                    g.playerAction(input);
                    player = g.getPlayer();
                    sc = true;
                }
                if (sc){
                    cout << "here" << endl;
                    bool x = g.update();
                    if(x) {
                        player->getPlayer()->clearBuff();
                        break;
                    }   
                } else {
                    cout << "Invalid Input." << endl;
                }
            }
            if (player->getPlayer()->getHP() <= 0) {
                cout << "==================================\n";
                cout << "             YOU lOST!\n";
                cout << "==================================\n";
                break;
            }
            if (restart) {
                restart = false;
                break;
            }
            g.level++;
        }

        if (g.level == 6) {
            int gold = player->getPlayer()->getGold();
            cout << "============================\n";
            cout << "            YOU WIN.\n";
            cout << "       FINAL SCORE: " << gold  << "\n";
            cout << "============================\n\n";
            return ;          
        }
    }
}

void Game::playGame(ifstream& map, string p){
    Grid g;
    string race;
    float Gold;
    int HP;
    int Atk;
    int Def;
    int barriersuite;
    ifstream data{p};
    while(true){
        
        data >> g.level;
        data >> race;
        data >> Gold;
        data >> HP;
        data >> Atk;
        data >> Def;
        data >> barriersuite;
        break;
    }
    data.close();
    bool start = true;
    string input;
    shared_ptr<Cell> player;
    bool restart = false;
    cout << "====================================\n";
    cout << "       Welcome back to CC3k!\n";
    cout << "====================================\n";
    while(true){ 


        while (g.level <= 5) {

            
            if(!barriersuite){
                int chance = rand() % 1;
                if (chance || g.level == 5) barriersuite = 1;
            }
            
                      
            if(start) {
                char r = tolower(race[0]);
                g.loadGame(map,r);
                map.close();
                if(barriersuite == 1) {
                    g.setBarrierSuite();
                    barriersuite++;
                }
                g.getPlayer()->getPlayer()->setAtk(Atk);
                g.getPlayer()->getPlayer()->setDef(Def);
                g.getPlayer()->getPlayer()->setGold(Gold);
                g.getPlayer()->getPlayer()->setHP(HP);
                g.getPlayer()->getPlayer()->barrierSuite = barriersuite;
                
                player = g.getPlayer();
                start = false;   
            }
            if(g.level != 1){
                g.loadGame(map,'N',player->getPlayer());
                map.close();
                if(barriersuite == 1) {
                    g.setBarrierSuite();
                    barriersuite++;
                }
                g.action += "PC find the Stair and has arrived to floor ";
                g.action += to_string(g.level);
                g.action += "! (All Buff cleared) ";
            }

            bool sc = true;
            while(player->getPlayer()->getHP() > 0) {
                player->checkStair();
                string d;
                if (sc) {
                    g.printMap();
                }
                sc = false;
                cout << "Command: ";
                cin >> input;
                
                if(input == "r") {
                    cout << "================================\n";
                    cout << "         PC reset the game\n";
                    cout << "================================\n";
                    g.level = 1;
                    restart = true;
                    break;
                } else if (input == "q") {
                    return;
                } else if (input == "s"){
                    cout << "Where you wish to save: ";
                    string filename;
                    cin >> filename;
                    saveGame(g,filename);
                    cout << "Saved! " << endl;
                    return;
                } else if (checkInput(input)){
                    g.playerAction(input);
                    player = g.getPlayer();
                    sc = true;
                }
                if (sc){
                    cout << "here" << endl;
                    bool x = g.update();
                    if(x) {
                        player->getPlayer()->clearBuff();
                        break;
                    }   
                } else {
                    cout << "Invalid Input." << endl;
                }
            }
            if (player->getPlayer()->getHP() <= 0) {
                cout << "==================================\n";
                cout << "             YOU lOST!\n";
                cout << "==================================\n";
                break;
            }
            if (restart) {
                restart = false;
                break;
            }
            g.level++;
        }

        if (g.level == 6) {
            int gold = player->getPlayer()->getGold();
            cout << "============================\n";
            cout << "            YOU WIN.\n";
            cout << "       FINAL SCORE: " << gold  << "\n";
            cout << "============================\n\n";
            return ;          
        }
    }
}

void Game::saveGame(Grid& g, string filename){
    ofstream archive {filename};
    string data = "data_" + filename;
    ofstream playerData {data};
    for(int i = 0; i < 25; i++){
        for(int j = 0; j < 79; j++){
            if(g.getGrid()[i][j]->getDisplay() == 'P' || g.getGrid()[i][j]->getDisplay() == 'G'){
                int v = (int)g.getGrid()[i][j]->getItem()->getVaule();
                switch (v) {
                case 10 :   archive << 0; break;
                case 11 :   archive << 1; break;
                case 12 :   archive << 2; break;
                case 13 :   archive << 3; break;
                case 14 :   archive << 4; break;
                case 15 :   archive << 5; break;
                case 1: archive << 6; break;
                case 2: archive << 7; break;
                case 4: archive << 8; break;
                case 6: archive << 9; break;
                }
            }else if(g.getGrid()[i][j]->checkStair()){
                archive << "\\";
            }else if(g.getGrid()[i][j]->getDisplay() == '@'){
                playerData << g.level << endl;
                playerData << g.getGrid()[i][j]->getPlayer()->getRace() << endl;
                playerData << g.getGrid()[i][j]->getPlayer()->getGold() << endl;
                playerData << g.getGrid()[i][j]->getPlayer()->getHP() << endl;
                playerData << g.getGrid()[i][j]->getPlayer()->getAtk() << endl;
                playerData << g.getGrid()[i][j]->getPlayer()->getDef() << endl;
                if(g.getGrid()[i][j]->getPlayer()->barrierSuite){
                    playerData << 1 << endl;
                }else {
                    playerData << 0 << endl;
                }
                archive << g.getGrid()[i][j]->getDisplay();
            }else{
                archive << g.getGrid()[i][j]->getDisplay();
            }
        }
            
        archive << endl;
    }
    archive.close();
}

