#include "constants.h"
#include "game.h"
#include "Pinky.h"

Pinky::Pinky(Game * game_)
{
    game = game_;
    color = COLOR_PINKY;
    dir_ = UP;
    if (game->difficulty>1)
        mode = CHASE;
    else{
        mode = WAIT;
        wait_timer = -1;
    }
}

/// Pinky's goal tile is 4 tiles in front of Pacman
void Pinky::GetChaseGoal(int & x, int & y)const
{
    int dir;
    game->GetPacmanLocation(x, y, dir);
    switch (dir)
    {
    case UP:
        y += 4;
        break;
    case RIGHT:
        x += 4;
        break;
    case DOWN:
        y -= 4;
        break;
    case LEFT:
        x -= 4;
        break;
    }
}
