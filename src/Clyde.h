#ifndef CLYDE_H
#define CLYDE_H
#include "ghost.h"

class Game;

class Clyde : public Ghost {
public:
    Clyde(Game * game_);
    ~Clyde(){};
private:
    void GetChaseGoal(int & x, int & y)const;
};

#endif /* CLYDE_H */

