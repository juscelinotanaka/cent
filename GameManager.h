//
// Created by Juscelino Tanaka on 16/03/18.
//

#ifndef CENT_GAMEMANAGER_H
#define CENT_GAMEMANAGER_H


#include "Mushroom.h"
#include "Ghost.h"

class GameManager {
public:
    static void PrepareGame();
    static void StartGame();

    // list of mushrooms on scene
    static std::vector<Mushroom *> mushrooms;
    static std::vector<Mushroom *> mushroomPool;
    static std::vector<Ghost *> ghosts;

    static void MushroomDestroyed(Mushroom *m);
    static Ghost *GetPreviousGhost(Ghost *me);

    static bool isGameStarted();

    static void GhostShot(Vector2 position);

private:
    static bool gameStarted;

    // a mushroom to hold the shared texture pool to reduce memory usage
    static Mushroom * mushroomTemplate;
    static int mushroomsDestroyed;

    static Ghost * ghostTemplate;
    static int ghostsDestroyed;

    static Mushroom *CreateNewMushroom();

};


#endif //CENT_GAMEMANAGER_H
