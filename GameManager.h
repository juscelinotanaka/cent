//
// Created by Juscelino Tanaka on 16/03/18.
//

#ifndef CENT_GAMEMANAGER_H
#define CENT_GAMEMANAGER_H


#include "Mushroom.h"
#include "Ghost.h"
#include "Player.h"

class GameManager {
public:
    static void PrepareGame();
    static void StartGame();

    static void MushroomDestroyed(Mushroom *m, bool skipScore = false);
    static Ghost *getPreviousGhost(Ghost *me);

    static bool isGameStarted();

    static void GhostShot(Ghost *ghost);

    static std::vector<Ghost*> getTailWithHead(Ghost *pGhost);

    static void PlayerDies();

    static bool hasMushroomAt(Vector2 pos);

private:
    // list of mushrooms on scene
    static std::vector<Mushroom *> mushrooms;
    static std::vector<Mushroom *> mushroomPool;
    static std::vector<Ghost *> ghosts;

    static bool gameStarted;

    // a mushroom to hold the shared texture pool to reduce memory usage
    static Mushroom * mushroomTemplate;
    static int mushroomsDestroyed;

    static Ghost * ghostTemplate;
    static int ghostsDestroyed;

    static Mushroom *CreateNewMushroom();

    static Player *player;

    static Mushroom *GetMushroomFromPool();

    static void CheckWinningCondition();

    static void RespawnGhost();

    static void ResetHead();

    static bool grid[30][30];
};


#endif //CENT_GAMEMANAGER_H
