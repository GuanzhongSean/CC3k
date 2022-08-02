#ifndef _PHOENIX_H_
#define _PHOENIX_H_
#include "player.h"
#include "enemy.h"


class Phoenix : public Enemy{
public:
    Phoenix();
    string attack( shared_ptr<Player>& player ) override;
};

#endif
