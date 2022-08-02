#ifndef _TROLL_H_
#define _TROLL_H_
#include "player.h"
#include "enemy.h"


class Troll : public Enemy{
public:
    Troll();
    string attack( shared_ptr<Player>& player ) override;
    
};

#endif
