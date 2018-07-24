#include "constants.h"
#include "game.h"
#include "Inky.h"

Inky::Inky(Game * game_)
{
    game = game_;
    color = COLOR_INKY;
    dir_ = UP;
    if (game->difficulty>2)
        mode = CHASE;
    else{
        mode = WAIT;
        wait_timer = -1;
    }
}

/// Inky's goal tile depends on Pacman's location, Pacman's direction and Blinky's location
void Inky::GetChaseGoal(int & x1, int & y1) const
{
    int dir1;
    game->GetPacmanLocation(x1, y1, dir1);
    switch (dir1)
    {
    case UP:
        y1 += 2;
        break;
    case RIGHT:
        x1 += 2;
        break;
    case DOWN:
        y1 -= 2;
        break;
    case LEFT:
        x1 -= 2;
        break;
    }
    int x2, y2;
    game->GetBlinkyLocation(x2, y2);
    x1 = 2 * x1 - x2;
    y1 = 2 * y1 - y2;
}
