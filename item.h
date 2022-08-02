#ifndef __ITEM_H__
#define __ITEM_H__

#include "player.h"
#include <string>

using namespace std;

class Item{
    char Name;
    string Real_name;


public:
    Item(char Name = ' ', string real_name = "");
    char getName();
    string getReal_name();
    virtual void changeState() {}
    virtual string useItem(Player &player) = 0;
    virtual float getVaule() = 0;
};

#endif
