
#ifndef BLINKY_H
#define BLINKY_H
#include "ghost.h"

class Game;

class Blinky : public Ghost{
public:
    Blinky(Game * game_);
    ~Blinky(){};
private:
    void GetChaseGoal(int & x, int & y)const;
};

#endif /* BLINKY_H */

