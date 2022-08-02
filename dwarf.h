#ifndef _DWARF_H_
#define _DWARF_H_

#include "player.h"
#include "enemy.h"

class Dwarf : public Player {
public:
    Dwarf();
    void addGold(float n) override;
    string attack(shared_ptr<Enemy>& e) override;
};

#endif
