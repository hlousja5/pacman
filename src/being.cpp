#include <ncurses.h>
#include "constants.h"
#include "being.h"
#include "game.h"
#include <iostream>

void Being::GetLocation(int & x, int & y) const
{
    x = x_;
    y = y_;
}

int Being::GetX() const
{
    return x_;
}

int Being::GetY() const
{
    return y_;
}

void Being::SetStartLocation(int x, int y)
{
    x_start = x;
    y_start = y;
    SetLocation(x, y);
}

void Being::SetLocation(int x, int y)
{
    x_ = x;
    y_ = y;
}

void Being::Hide() const
{
    mvaddch(y_ + 2, x_, game->GetChar(x_, y_));
}

void Being::Show() const
{
    if (color != COLOR_PACMAN)
        mvaddch(y_ + 2, x_, GHOST_ICON | COLOR_PAIR(color) | A_BOLD);
    else
        mvaddch(y_ + 2, x_, ICONS[dir_] | COLOR_PAIR(color) | A_BOLD);
}

int Being::GetDirection() const
{
    return dir_;
}

void Being::SetDirection(int direction)
{
    dir_ = direction;
}

void Being::GetToStart()
{
    Hide();
    x_ = x_start;
    y_ = y_start;
    Show();
}