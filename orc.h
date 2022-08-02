#ifndef _ORC_H_
#define _ORC_H_

#include "player.h"
#include "enemy.h"

class Orc : public Player {
public:
    Orc();
    void addGold(float n) override;
    string attack(shared_ptr<Enemy>& e) override;
};

#endif
