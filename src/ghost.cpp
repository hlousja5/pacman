#include <math.h>
#include "constants.h"
#include "game.h"
#include "ghost.h"

/// Stops ghost's movement for 15 "turns"
void Ghost::StopMovement()
{
    mode = WAIT;
    wait_timer += 15;
}

/// Either decrements wait timer, continues in previous path, or decides which way to go if at intersection
void Ghost::Move()
{
    if (mode == WAIT)
    {
        wait_timer--;
        Show();
        if (wait_timer == 0)
            mode = CHASE;
        return;
    }
    int newDir = DecideDirection();
    Hide();
    SetDirection(newDir);
    switch (newDir)
    {
    case UP:
        y_--;
        break;
    case RIGHT:
        x_++;
        x_ %= LEVEL_WIDTH;
        break;
    case DOWN:
        y_++;
        break;
    case LEFT:
        x_--;
        x_ += LEVEL_WIDTH;
        x_ %= LEVEL_WIDTH;
        break;
    }
    Show();
}

/// Decides the route a ghost should take
int Ghost::DecideDirection() const
{
    /// Get available routes
    int possibleDirections[5];
    game->GetOpenDirections(x_, y_, dir_, possibleDirections);

    /// if no route available, turn back;
    if (possibleDirections[0] == 0)
        return (dir_ + 2) % 4;

    /// if one route available, go that way
    if (possibleDirections[0] == 1)
        for (int i = 0; i < 4; i++)
        {
            if (possibleDirections[i + 1] == 1)
                return i;
        }

    /// if more routes available, pick the closest to goal
    int distance;
    int minDistance = 999;
    int minDirection;
    int x1, y1;
    GetChaseGoal(x1, y1);
    for (int i = 0; i < 4; i++)
    {
        if (possibleDirections[i + 1] == 0)
            continue;
        switch (i)
        {
        case UP:
            distance = sqrt(pow(fabs(x_ - x1), 2) + pow(fabs(y_ - 1 - y1), 2));
            break;
        case RIGHT:
            distance = sqrt(pow(fabs(x_ + 1 - x1), 2) + pow(fabs(y_ - y1), 2));
            break;
        case DOWN:
            distance = sqrt(pow(fabs(x_ - x1), 2) + pow(fabs(y_ + 1 - y1), 2));
            break;
        case LEFT:
            distance = sqrt(pow(fabs(x_ - 1 - x1), 2) + pow(fabs(y_ - y1), 2));
            break;
        }
        if (distance < minDistance)
        {
            minDistance = distance;
            minDirection = i;
        }
    }
    return minDirection;
}
