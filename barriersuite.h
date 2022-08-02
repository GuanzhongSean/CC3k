#ifndef __BARRIERSUITE_H_
#define __BARRIERSUITE_H__
#include <string>
#include "item.h"
#include "player.h"

class BarrierSuite: public Item{
    bool is_dead;
public:
    BarrierSuite(bool is_dead = false);
    void setIs_dead(bool status);
    string useItem(Player &player) override;
    float getVaule() override;
};

#endif
