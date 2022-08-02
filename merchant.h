#ifndef _MERCHANT_H_
#define _MERCHANT_H_
#include "player.h"
#include "enemy.h"
#include "grid.h"


class Merchant : public Enemy {
public:
    //static bool hostile;
    Merchant();
   // bool isHostile();
    //void setHostile();
    string attack( shared_ptr<Player>& player ) override;
    
};

#endif
