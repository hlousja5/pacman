#include <math.h>
#include "constants.h"
#include "game.h"
#include "Clyde.h"

Clyde::Clyde(Game * game_)
{
    game = game_;
    color = COLOR_CLYDE;
    dir_ = UP;
    corner_x = 0;
    corner_y = LEVEL_HEIGHT - 1;
    mode = CHASE;
    if (game->difficulty>3)
        mode = CHASE;
    else{
        mode = WAIT;
        wait_timer = -1;
    }
}

/// Clyde's goal tile is either Pacman or bottom left corner, based on the distance from Pacman
void Clyde::GetChaseGoal(int & x, int & y) const
{
    int dir;
    game->GetPacmanLocation(x, y, dir);
    if ((fabs(x_ - x) + fabs(y_ - y)) < 8)
    {
        x = corner_x;
        y = corner_y;
    }
}
