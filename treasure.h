#ifndef __TREASURE_H__
#define __TREASURE_H__
#include "item.h"
#include "player.h"
#include <string>

class Treasure: public Item{
    float Gvalue;
    bool is_dead;
public:
    Treasure(float Gvalue, bool is_dead = true);
    void setIs_dead(bool status);
    string real_name(float v);
    void changeState() override {
        is_dead = true;
    }
    string useItem(Player &player) override;
    float getVaule() override;
};

#endif
