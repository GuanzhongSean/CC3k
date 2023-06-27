#ifndef _CHAMBER_H_
#define _CHAMBER_H_

#include <vector>

using namespace std;

struct Pos {
    int x;
    int y;
    Pos(int x, int y);
};


class Chamber{
    int totalCells = 638;
    vector<Pos> chamberCell;
    vector<Pos> chamber1;
    vector<Pos> chamber2;
    vector<Pos> chamber3;
    vector<Pos> chamber4;
    vector<Pos> chamber5;
public:
    Pos randomCell();
    void attachChamber(Pos);
};


#endif
