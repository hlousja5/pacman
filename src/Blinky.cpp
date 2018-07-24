#include "game.h"
#include "Blinky.h"


Blinky::Blinky(Game * game_)
{
    game = game_;
    color = COLOR_BLINKY;
    dir_ = LEFT;
    if (game->difficulty>0)
        mode = CHASE;
    else{
        mode = WAIT;
        wait_timer = -1;
    }
}

/// Blinky's goal tile is always Pacman
void Blinky::GetChaseGoal(int & x, int & y) const
{
    int dir;
    game->GetPacmanLocation(x, y, dir);
}
