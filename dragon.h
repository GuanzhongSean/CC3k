#ifndef _DRAGON_H_
#define _DRAGON_H_

#include "enemy.h"
#include "cell.h"

using namespace std;

class Dragon : public Enemy {
    shared_ptr<Cell> horde;
public:
    Dragon();
    void setHorde(shared_ptr<Cell>) override;
    string attack( shared_ptr<Player>& player ) override;
    shared_ptr<Cell> getHorde() override;
    bool isDead() override;
};

#endif
