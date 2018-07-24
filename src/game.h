
#ifndef GAME_H
#define GAME_H
#include <vector>
#include <string>
#include "constants.h"
using namespace std;

class Ghost;
class Pacman;

/** 
* Game's engine.
*   Controls the whole game, keeps track of everything.
*/

class Game {
public:
    Game();
    ~Game();
    void Start();
    void SuperPellet();
    void LittlePellet();
    void SetChar(int x, int y, char c);

    bool IsOpen(int x, int y, int dir)const;
    void GetPacmanLocation(int & x, int & y, int & dir)const;
    void GetOpenDirections(int x, int y, int dir, int possibleDirections[])const;
    void GetBlinkyLocation(int & x, int & y)const;
    char GetChar(int x, int y)const;
    int difficulty;
private:
    void SetDifficulty();
    void ResetPositions();
    bool CheckForDeath();
    void LoadMap();
    void InitNCurses();
    void Go();

    void HideMap()const;
    void ShowMap()const;
    void ShowWelcome() const;
    void ShowInfo()const;
    void UpdateInfo()const;
    
    Pacman * pacman;
    vector<Ghost*> ghosts;
    char map[LEVEL_HEIGHT][LEVEL_WIDTH];
    int lives;
    int score;
    
    int multiplyer;
    int pelletsLeft;
    int pelletCount;
    string mapName;
};

#endif /* GAME_H */

