#ifndef _VAMPIRE_H_
#define _VAMPIRE_H_
#include "player.h"
#include "enemy.h"


class Vampire : public Enemy{
public:
    Vampire();
    string attack( shared_ptr<Player>& player ) override;
};

#endif
