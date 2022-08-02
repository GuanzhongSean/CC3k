#ifndef _ELVES_H_
#define _ELVES_H_

#include "player.h"
#include "enemy.h"

class Elves : public Player {
public:
    Elves();
    string attack(shared_ptr<Enemy>& e) override;
};

#endif
