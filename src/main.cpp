#include <cstdlib>
#include <ncurses.h>
#include <iostream>
#include "constants.h"
#include "game.h"
#include "being.h"

using namespace std;

int main() {
    Game *game = new Game();
    game->Start();
    delete game;
    return 0;
}

