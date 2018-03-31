//
// Created by Juscelino Tanaka on 16/03/18.
//

#ifndef CENT_GAMEMANAGER_H
#define CENT_GAMEMANAGER_H


#include "Mushroom.h"
#include "Ghost.h"
#include "Player.h"
#include "Logo.h"

class GameManager {
public:
    static void PrepareGame();
    static void StartGame();

    static void MushroomDestroyed(Mushroom *m, bool skipScore = false);
    static Ghost *getPreviousGhost(Ghost *me);

    static bool isGameStarted();
    static void GhostShot(Ghost *ghost);
    static void PlayerDies();
    static void PrintGrid();
    static bool hasMushroomAt(Vector2 pos);
    static int mushroomsDestroyed;
    static int partsDestroyed;
    static int ghostKills;

    static int deaths;

    static int getTotalScore();

private:
    static Player *player;
    static bool gameStarted;
    static void CheckWinningCondition();

    // list of mushrooms on scene
    static std::vector<Mushroom *> mushrooms;
    static std::vector<Mushroom *> mushroomPool;
    static std::vector<Ghost *> ghosts;

    // a mushroom to hold the shared texture pool to reduce memory usage
    static Mushroom * mushroomTemplate;

    static Mushroom *CreateNewMushroom();
    static Mushroom *GetMushroomFromPool();

    // ghost
    static Ghost * ghostTemplate;
    static void RespawnGhost();
    static void ResetHead();

    static bool grid[30][30];
    static Logo *logo;

    static void SpawnGame();
};


#endif //CENT_GAMEMANAGER_H
