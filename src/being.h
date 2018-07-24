#ifndef BEING_H
#define BEING_H
#include <math.h>
using namespace std;

class Game;

/**
*   Tempate class for movable objects, Pacman and Ghosts.
*   Implements methods for manipulating with objects location on a game map.
*/

class Being {
protected:
    virtual ~Being(){};
    int x_, y_;
    int x_start, y_start;
    int dir_;
    int color;
    Game* game;
public:
    virtual void Move() = 0;
    void Show() const;
    void Hide() const;
    void GetLocation(int & x_, int & y_) const;
    int  GetX() const;
    int  GetY() const;
    void SetStartLocation(int x, int y);
    void SetLocation(int x, int y);
    int  GetDirection() const;
    void SetDirection(int direction);
    void GetToStart();
};

#endif /* BEING_H */
