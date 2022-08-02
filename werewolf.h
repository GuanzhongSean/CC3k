#ifndef _WEREWOLF_H_
#define _WEREWOLF_H_

#include "enemy.h"


class Werewolf : public Enemy{
public:
    Werewolf();
    string attack( shared_ptr<Player>& player ) override;

};

#endif
