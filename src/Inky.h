#ifndef INKY_H
#define INKY_H
#include "ghost.h"

class Game;

class Inky : public Ghost{
public:
    Inky(Game * game_);
    ~Inky(){};
private:
    void GetChaseGoal(int & x, int & y)const;
};

#endif /* INKY_H */

