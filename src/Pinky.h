#ifndef PINKY_H
#define PINKY_H
#include "ghost.h"

class Game;

class Pinky : public Ghost{
public:
    Pinky(Game * game_);
    ~Pinky(){};
private:
    void GetChaseGoal(int & x, int & y)const;
};

#endif /* PINKY_H */

