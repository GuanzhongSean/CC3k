#ifndef _GOBLIN_H_
#define _GOBLIN_H_
#include "player.h"
#include "enemy.h"


class Goblin : public Enemy{
public:
    Goblin();
    string attack( shared_ptr<Player>& player ) override;
};

#endif
