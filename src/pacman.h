#ifndef PACMAN_H
#define PACMAN_H
#include "being.h"

class Game;
/**
*	Class for player controlled Pacman.
*	Implements methods for chatching user input and controlling pacman' movement 
* 	based on that input.
*/
class Pacman : public Being {
public:
    Pacman(Game * game_);
     ~Pacman(){};
    void Move();
private:
    int CatchKeyStroke()const;
    void MoveAndEat(int direction);
    int dirWish;
    int dirWishCounter;
};

#endif /* PACMAN_H */

