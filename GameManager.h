//
// Created by Juscelino Tanaka on 16/03/18.
//

#ifndef CENT_GAMEMANAGER_H
#define CENT_GAMEMANAGER_H


#include "MushroomObject.h"

class GameManager {
public:
    static void PrepareGame();
    static void StartGame();

    // list of mushrooms on scene
    static std::vector<MushroomObject *> mushrooms;
    static std::vector<MushroomObject *> mushroomPool;

    static void MushroomDestroyed(MushroomObject *m);

private:
    // a mushroom to hold the shared texture pool to reduce memory usage
    static MushroomObject * mushroomPrefab;
    static int mushroomsDestroyed;

    static MushroomObject *CreateNewMushroom();
};


#endif //CENT_GAMEMANAGER_H
