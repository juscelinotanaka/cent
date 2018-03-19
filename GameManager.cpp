//
// Created by Juscelino Tanaka on 16/03/18.
//

#include <sstream>
#include "GameManager.h"
#include "PlayerObject.h"

MushroomObject * GameManager::mushroomPrefab;
int GameManager::mushroomsDestroyed = 0;
std::vector<MushroomObject *> GameManager::mushrooms;
std::vector<MushroomObject *> GameManager::mushroomPool;


void GameManager::PrepareGame() {

    // create player object and add it to the scene
    PlayerObject * s = new PlayerObject("Main Char");
    s->scale = Vector2::one * 2;
    CoreEngine::AddSceneObject(s);

    // prepare one mushroom to share texture with all others
    mushroomPrefab = new MushroomObject("Mushroom Prefab");
    mushroomPrefab->SetImage("data/Mushroom1.bmp");
    mushroomPrefab->SetImage("data/Mushroom2.bmp", true);
    mushroomPrefab->SetImage("data/Mushroom3.bmp", true);
    mushroomPrefab->SetImage("data/Mushroom4.bmp", true);
}

void GameManager::StartGame() {

    srand(time(NULL));

    for (int i = 0; i < 28; ++i) {
        MushroomObject * m = CreateNewMushroom();

        mushrooms.push_back(m);

        int column = rand() % 30;
        m->position = Vector2(column, i) * 16;

        CoreEngine::AddSceneObject(m);
    }
}

void GameManager::MushroomDestroyed(MushroomObject *m) {
    m->enable = false;
    mushrooms.erase(std::remove(mushrooms.begin(), mushrooms.end(), m), mushrooms.end());
    mushroomPool.push_back(m);
    mushroomsDestroyed++;
}

MushroomObject * GameManager::CreateNewMushroom() {
    MushroomObject * m = new MushroomObject("Mushrumor");

    // avoid reallocating new textures to save memory
    m->setSharedTexture(mushroomPrefab->getSharedTexture());
    m->tag = "Mushroom";
    m->SetImageFromPool(0);
    m->imageSize = mushroomPrefab->imageSize;
    m->scale = Vector2::one * 2;

    return m;
}
