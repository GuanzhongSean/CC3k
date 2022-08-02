#ifndef _HUMAN_H_
#define _HUMAN_H_

#include "player.h"
#include "enemy.h"

class Human: public Player {
public:
    Human();
    string attack(shared_ptr<Enemy>& e) override;
};

#endif
