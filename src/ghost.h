
#ifndef GHOST_H
#define GHOST_H
#include <iostream>
#include <math.h>
#include "being.h"

class Game;

/**
*   Template class for ghosts.
*   Implements methods for manipulating ghosts' movement  
*/
class Ghost : public Being{
public:
    virtual ~Ghost(){};
    int DecideDirection() const;
    void Move();
    void StopMovement();
    /// Finds a goal tile for a ghost to pursue
    virtual void GetChaseGoal(int & x, int & y) const = 0;
    int wait_timer;
    int mode;
protected:
    int corner_x;
    int corner_y;
};
#endif /* GHOST_H */

