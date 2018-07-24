#include <ncurses.h>
#include <iostream>
#include <unistd.h>
#include "game.h"
#include "pacman.h"
int iter = 0;

Pacman::Pacman(Game * game_)
{
    game = game_;
    color = COLOR_PACMAN;
    dir_ = LEFT;
    dirWish = -1;
    dirWishCounter = 0;
}

/// Tries to move pacman based on input and current direction
void Pacman::Move()
{
    // bool errflag=false;
    int newDir = CatchKeyStroke();
    if (newDir == -1)
    {
        //   errflag=true;
        if (dirWish != -1)
        {
            newDir = dirWish;
            dirWishCounter--;
        }
        else
            newDir = dir_;

        if (dirWishCounter == 0)
            dirWish = -1;
    }
    else
    {
        dirWish = newDir;
        dirWishCounter = 3;
    }
    if (game->IsOpen(x_, y_, newDir))
    {
        MoveAndEat(newDir);
    }
    else if (game->IsOpen(x_, y_, dir_))
    {
        MoveAndEat(dir_);
    }
}

/// Moves pacman one tile and eats a pellet 
void Pacman::MoveAndEat(int direction)
{
    Hide();
    SetDirection(direction);
    switch (direction)
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
    if (game->GetChar(x_, y_) == '.')
    {
        game->SetChar(x_, y_, ' ');
        game->LittlePellet();
    }
    if (game->GetChar(x_, y_) == 'o')
    {
        game->SetChar(x_, y_, ' ');
        game->SuperPellet();
    }
    Show();
}

/// Catches user input
int Pacman::CatchKeyStroke() const
{
    int ch = getch();
    if (ch == ERR)
    {
        return -1;
    }
    else
    {
        switch (ch)
        {
        case KEY_UP:
            return UP;
        case KEY_RIGHT:
            return RIGHT;
        case KEY_DOWN:
            return DOWN;
        case KEY_LEFT:
            return LEFT;
        }
    }
    return -1;
}