#include <ncurses.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unistd.h>
#include "game.h"
#include "ghost.h"
#include "pacman.h"
#include "Inky.h"
#include "Pinky.h"
#include "Clyde.h"
#include "Blinky.h"

Game::Game(){}

Game::~Game()
{
    delete pacman;
    for (unsigned i = 0; i < ghosts.size(); i++)
    {
        delete ghosts[i];
    }
}

/// Loads map from a file
void Game::LoadMap()
{
    ifstream ifs;
    ifs.open(mapName, ifstream::in);
    char c;
    pelletCount = 0;
    for (int i = 0; i < LEVEL_HEIGHT; i++)
    {
        for (int j = 0; j < LEVEL_WIDTH; j++)
        {
            c = ifs.get();
            if (c == '#' || c == '.' || c == 'o' || c == '_')
            {
                map[i][j] = c;
            }
            else
                map[i][j] = ' ';
            if (c == '.' || c == 'o')
            pelletCount++;pelletsLeft = pelletCount;
            lives = 3;
            switch (c)
            {
            case 'p':
                pacman = new Pacman(this);
                pacman->SetStartLocation(j, i);
                break;
            case 'B':
                ghosts.push_back(new Blinky(this));
                ghosts.back()->SetStartLocation(j, i);
                break;
            case 'P':
                ghosts.push_back(new Pinky(this));
                ghosts.back()->SetStartLocation(j, i);
                break;
            case 'I':
                ghosts.push_back(new Inky(this));
                ghosts.back()->SetStartLocation(j, i);
                break;
            case 'C':
                ghosts.push_back(new Clyde(this));
                ghosts.back()->SetStartLocation(j, i);
                break;
            }
        }
        c = ifs.get();
    }
}

/// Hides map and prints final score
void Game::HideMap() const
{
    nodelay(stdscr,FALSE);
    move(0,0);
    for (int i = 0; i < LEVEL_HEIGHT+5; i++)
    {
        for (int j = 0; j < LEVEL_WIDTH; j++)
            addch(' ');
        addch('\n');
    }
    move (LEVEL_HEIGHT/2, LEVEL_WIDTH/2-5);
    if (pelletsLeft>0)
        addstr("You died");
    else
        addstr("You won!!");
    move (LEVEL_HEIGHT/2+1, LEVEL_WIDTH/2-5);
    addstr ("Your score: ");
    printw(to_string(score).c_str());
    refresh();
    sleep(1);
    getch();
}

/// Prints game map
void Game::ShowMap() const
{
    // Show game map
    move(0, 0);
    printw("\n");
    printw("\n");
    for (int i = 0; i < LEVEL_HEIGHT; i++)
    {
        for (int j = 0; j < LEVEL_WIDTH; j++)
        {
            if (map[i][j] == '#')
                addch('#' | COLOR_PAIR(COLOR_WALL));
            else
                addch(map[i][j]);
        }
        printw("\n");
    }

    // Show Pacman
    int x, y;
    pacman->GetLocation(x, y);
    mvaddch(y + 2, x, ICONS[pacman->GetDirection()] | COLOR_PAIR(COLOR_PACMAN) | A_BOLD);

    // Show ghosts
    for (unsigned int i = 0; i < ghosts.size(); i++)
    {
        ghosts[i]->GetLocation(x, y);
        mvaddch(y + 2, x, '"' | COLOR_PAIR(4 + i) | A_BOLD);
    }
    refresh();
    getch();
    nodelay(stdscr, TRUE);
}

/// Shows game info ( lives, score, pellets left).
void Game::ShowInfo() const
{
    move(0, 3);
    addstr("SCORE");
    move(1, 3);
    addstr("00");
    move(LEVEL_HEIGHT + 2, 0);
    addstr("Pellets left:");
    move(LEVEL_HEIGHT + 2, 13);
    addstr(to_string(pelletsLeft).c_str());
    move(LEVEL_HEIGHT + 3, 0);
    for (int i = 0; i < lives; i++)
    {
        addch('<' | COLOR_PAIR(COLOR_PACMAN) | A_BOLD);
        addch(' ');
    }
}

/// Updates game info.
void Game::UpdateInfo() const
{
    move(1, 4);
    printw(to_string(score).c_str());
    mvprintw(LEVEL_HEIGHT + 2, 13, "   ");
    move(LEVEL_HEIGHT + 2, 13);
    printw(to_string(pelletsLeft).c_str());
    move(LEVEL_HEIGHT + 3, 0);
    for (int i = 0; i < lives; i++)
    {
        addch('<' | COLOR_PAIR(COLOR_PACMAN) | A_BOLD);
        addch(' ');
    }
    for (int i = lives; i < 5; i++)
        addstr("  ");
}

/// Initialization of NCurses
void Game::InitNCurses()
{
    initscr();
    noecho();
    curs_set(0);
    cbreak();
    keypad(stdscr, TRUE);
    start_color();
    init_pair(2, COLOR_BLUE, COLOR_BLUE);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_WHITE, COLOR_RED);
    init_pair(5, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(6, COLOR_BLACK, COLOR_CYAN);
    init_pair(7, COLOR_BLACK, COLOR_GREEN);
}

/// Shows welcome screen;
void Game::ShowWelcome() const
{
    move (LEVEL_HEIGHT/2, LEVEL_WIDTH/2-10);
    addstr("Choose a difficulty: (0-5)");
    refresh();
}

///
void Game::Start()
{
    InitNCurses();
    ShowWelcome();
    SetDifficulty();
    LoadMap();
    ShowMap();
    ShowInfo();
    Go();
    HideMap();
    endwin();
}

/// Sets the game difficulty by user input. Changes number of alive ghosts and what map is used.
void Game::SetDifficulty()
{
    char dif=getch();
    switch (dif) {
        case '0':
            difficulty = 0;
            mapName="map2.txt";
            break;
        case '1':
            difficulty = 1;
            mapName="map1.txt";
            break;
        case '2':
            difficulty = 2;
            mapName="map1.txt";
            break;
        case '3':
            difficulty = 3;
            mapName="map1.txt";
            break;
        case '4':
            difficulty = 4;
            mapName="map1.txt";
            break;
        default:
            difficulty = 5;
            mapName="map3.txt";
            break;
    }
}

/// Starts the actual gameplay loop.
void Game::Go()
{
    while (pelletsLeft != 0)
    {
        usleep(130000);
        pacman->Move();
        if (CheckForDeath())
            return;
        UpdateInfo();
        for (unsigned int i = 0; i < ghosts.size(); i++)
            ghosts[i]->Move();
        if (CheckForDeath())
            return;
        UpdateInfo();
    }
    usleep(150000);
}

/// Resets everyone's position when Pacman loses a life
void Game::ResetPositions()
{
    pacman->GetToStart();
    for (unsigned int i = 0; i < ghosts.size(); i++)
    {
        ghosts[i]->GetToStart();
        ;
    }
    sleep(2);
}

/// Checks for collisions of Pacman with ghosts
bool Game::CheckForDeath()
{
    int x, y, x1, y1;
    pacman->GetLocation(x, y);
    for (unsigned int i = 0; i < ghosts.size(); i++)
    {
        ghosts[i]->GetLocation(x1, y1);
        if (x == x1 && y == y1)
        {
            if (ghosts[i]->mode==CHASE)
            {
                multiplyer=1;
                lives--;
                refresh();
                ResetPositions();
                break;
            }
            else if ((ghosts[i]->wait_timer)>0)
            {
                ghosts[i]->GetToStart();
                score+=100*multiplyer;
                multiplyer*=2;
            }
        }
    }
    if (lives == 0)
    {
        refresh();
        UpdateInfo();
        return true;
    }
    refresh();
    return false;
}

/// Returns Pacman's l
void Game::GetPacmanLocation(int & x, int & y, int & dir) const
{
    pacman->GetLocation(x, y);
    dir = pacman->GetDirection();
}

void Game::GetBlinkyLocation(int & x, int & y) const
{
    ghosts[0]->GetLocation(x, y);
}

//Checks if there is a wall in front of pacman
bool Game::IsOpen(int x, int y, int dir) const
{
    switch (dir)
    {
    case UP:
        return (map[y - 1][x] != '#');
        break;
    case RIGHT:
        return (map[y][x + 1] != '#' || x == LEVEL_WIDTH - 1);
        break;
    case DOWN:
        return (map[y + 1][x] != '#');
        break;
    default:
        return (map[y][x - 1] != '#' || x == 0);
        break;
    }
}


void Game::GetOpenDirections(int x, int y, int dir, int possibleDirections[]) const
{
    possibleDirections[0] = 0;
    for (int d = 0; d < 4; d++)
    {
        if (d != (dir + 2) % 4 && IsOpen(x, y, d))
        {
            possibleDirections[d + 1] = 1;
            possibleDirections[0]++;
        }
        else
            possibleDirections[d + 1] = 0;
    }
}

char Game::GetChar(int x, int y) const
{
    return map[y][x];
}


void Game::SetChar(int x, int y, char c)
{
    map[y][x] = c;
}

void Game::SuperPellet()
{
    score += 50;
    pelletsLeft--;
    for (unsigned i = 0; i < ghosts.size(); i++)
        if (ghosts[i]->mode == CHASE)
        {
            ghosts[i]->mode = WAIT;
            ghosts[i]->wait_timer = 25;
        }
}

void Game::LittlePellet()
{
    score += 10;
    pelletsLeft--;
}
